"use strict";
const $ = (id) => document.getElementById(id);
const make = (tag, text = "", cls = "") =>
  Object.assign(document.createElement(tag), {
    textContent: text,
    className: cls,
  });
let m,
  q,
  revision = 0,
  dirRev = 0,
  draft = "",
  retry = false,
  page = 0,
  query = "",
  hits = [],
  candidates = [],
  scanned = 0;
const cache = new Map(),
  key = "nurse-practice-v1";
let state = {
  mode: "practice",
  pos: 1,
  wrongPos: 0,
  autoNext: true,
  answers: {},
  read: {},
  wrong: {},
};
try {
  Object.assign(state, JSON.parse(localStorage.getItem(key)) || {});
} catch {}
function save() {
  try {
    localStorage.setItem(key, JSON.stringify(state));
    $("saved").textContent = "进度已存于本机";
  } catch {
    $("saved").textContent = "浏览器无法保存进度";
  }
}
async function data(path) {
  if (!cache.has(path)) {
    const packed =
      path.startsWith("data-") && typeof DecompressionStream === "function";
    const task = fetch(packed ? path.replace(/\.json$/, ".pack") : path).then(
      (r) => {
        if (!r.ok) throw Error("数据载入失败");
        return packed
          ? new Response(
              r.body.pipeThrough(new DecompressionStream("gzip")),
            ).json()
          : r.json();
      },
    );
    cache.set(path, task);
    task.catch(() => cache.delete(path));
    if (cache.size > 48) cache.delete(cache.keys().next().value);
  }
  return cache.get(path);
}
async function item(id) {
  const batch = await data(
    m.base + "/q" + Math.floor((id - 1) / m.size) + ".json",
  );
  return batch[(id - 1) % m.size];
}
const wrongIds = () =>
  Object.keys(state.wrong)
    .map(Number)
    .sort((a, b) => a - b);
const current = () => (state.mode === "wrong" ? state.wrongPos : state.pos);
let heldBits = "";
function isHeld(id) {
  const i = id - 1;
  return Boolean(heldBits.charCodeAt(i >> 3) & (1 << i % 8));
}
function adjacent(step) {
  const id = current();
  if (state.mode === "wrong") {
    const ids = wrongIds();
    return ids[ids.indexOf(id) + step];
  }
  for (let next = id + step; next >= 1 && next <= m.total; next += step) {
    if (state.mode === "study" || !isHeld(next)) return next;
  }
}
function book(id) {
  return m.books.find((b) => id >= b.start && id <= b.end);
}
function stats() {
  const studying = state.mode === "study",
    limit = studying ? m.total : m.graded,
    n = Object.keys(studying ? state.read : state.answers).length;
  document.querySelector(".progress .small").textContent = studying
    ? "背题进度"
    : "做题进度";
  document.querySelector(".progressmeta span").textContent = studying
    ? "已浏览"
    : "已作答";
  $("done").textContent = n;
  $("total").textContent = "/ " + limit + " 题";
  $("bar").max = limit;
  $("bar").value = n;
  $("percent").textContent = Math.round((n * 100) / limit) + "%";
  $("wrongCount").textContent = wrongIds().length;
  for (const el of $("modes").children) {
    const active = el.dataset.mode === state.mode;
    el.classList.toggle("active", active);
    el.setAttribute("aria-pressed", active);
  }
}
function button(label, fn, cls = "") {
  const b = make("button", label, cls);
  b.onclick = fn;
  return b;
}
let advanceTimer;
async function load() {
  clearTimeout(advanceTimer);
  $("question").scrollTop = 0;
  const ticket = ++revision;
  retry = false;
  draft = "";
  q = null;
  stats();
  const ids = wrongIds();
  if (state.mode === "wrong" && !ids.includes(state.wrongPos))
    state.wrongPos = ids[0] || 0;
  const id = current();
  save();
  const wrap = $("question"),
    line = $("bookline");
  line.replaceChildren();
  wrap.replaceChildren();
  const inWrong = state.mode === "wrong",
    idx = inWrong ? ids.indexOf(id) : id - 1;
  $("prev").disabled = !adjacent(-1);
  $("next").disabled = !adjacent(1);
  if (!id) {
    line.textContent = "错题集";
    wrap.append(
      make("h2", "还没有错题", "empty"),
      make("p", "答错的题会自动收录在这里，可以随时回来重练。"),
    );
    return;
  }
  line.append(
    make("b", book(id).name + " · " + (id - book(id).start + 1)),
    make(
      "span",
      inWrong
        ? "错题 " + (idx + 1) + " / " + ids.length
        : "第 " + id + " / " + m.total + " 题",
    ),
  );
  wrap.textContent = "正在载入题目…";
  try {
    const rec = await item(id);
    if (ticket !== revision) return;
    q = rec;
    if (state.mode === "study") {
      state.read[id] = 1;
      save();
      stats();
    }
    retry = inWrong;
    render();
  } catch {
    if (ticket === revision)
      wrap.replaceChildren(button("载入失败，点击重试", load));
  }
}
function render() {
  const id = current(),
    wrap = $("question"),
    ans = q.answer || "",
    study = state.mode === "study",
    prior = state.answers[id];
  const show = study || (!retry && !!prior),
    multi = q.section?.includes("多选") || ans.length > 1;
  wrap.replaceChildren();
  const meta = make("div", "", "qmeta");
  meta.append(
    make("span", !ans ? "待核题" : multi ? "多选题" : "单选题", "tag"),
    make("span", ans ? "应选 " + ans.length + " 项" : "已保留原题"),
  );
  wrap.append(meta, make("h2", q.stem, "stem"));
  const choices = make("div", "", "choices");
  wrap.append(choices);
  for (const [letter, label] of Object.entries(q.options)) {
    const live = !show && !!ans,
      el = make(live ? "button" : "div", "", "choice");
    el.append(make("span", letter, "letter"), make("span", label));
    if (show && ans.includes(letter)) el.classList.add("right");
    if (show && !study && prior?.includes(letter) && !ans.includes(letter))
      el.classList.add("bad");
    if (live) {
      if (multi) {
        el.classList.toggle("selected", draft.includes(letter));
        el.setAttribute("aria-pressed", draft.includes(letter));
      }
      el.onclick = () => {
        if (!multi) return submit(letter);
        draft = draft.includes(letter)
          ? draft.replace(letter, "")
          : [...draft, letter].sort().join("");
        render();
      };
    }
    choices.append(el);
  }
  if (!show && ans && multi) {
    const b = button("提交所选答案", () => submit(draft), "primary");
    b.disabled = !draft;
    wrap.append(b);
  }
  if (show || !ans) {
    const f = make("div", "", "feedback");
    let title = !ans
      ? "答案待核 · 暂停判分"
      : study
        ? "参考答案 " + ans
        : prior === ans
          ? "回答正确 · " + ans
          : "回答有误 · 参考答案 " + ans;
    f.append(make("strong", title));
    if (show && !study && ans && prior !== ans)
      f.append(make("p", "你的选择 " + prior));
    const details = make("details");
    details.append(make("summary", ans ? "查看答案解析" : "查看待核原因"));
    if (q.explanation) details.append(make("p", q.explanation));
    else if (ans)
      details.append(
        make("p", "原文标记的答案为 " + ans + "。这道题的判断理由尚待补充。"),
      );
    const extraNote =
      q.note &&
      (!q.explanation || !q.note.startsWith(q.explanation)) &&
      (!q.explanation || !ans || !q.source_url);
    if (extraNote) details.append(make("p", q.note));
    if (!ans && !q.note && !q.explanation)
      details.append(make("p", "原文缺少足以核定答案的信息。"));
    if (q.original_answer && q.original_answer !== ans)
      details.append(make("p", "原文答案标记：" + q.original_answer));
    if (q.source_url && /^https?:\/\//.test(q.source_url)) {
      const a = make("a", "查看核查依据");
      a.href = q.source_url;
      a.target = "_blank";
      a.rel = "noopener noreferrer";
      details.append(a);
    }
    f.append(details);
    wrap.append(f);
    if (!study && ans)
      wrap.append(
        button(
          "重新作答",
          () => {
            clearTimeout(advanceTimer);
            retry = true;
            draft = "";
            render();
          },
          "retry",
        ),
      );
    if (state.mode === "wrong" && prior === ans && !retry)
      wrap.append(
        button(
          "移出错题集",
          () => {
            delete state.wrong[id];
            load();
          },
          "retry",
        ),
      );
  }
}
function submit(value) {
  if (!q || !value) return;
  const id = current();
  state.answers[id] = value;
  if (value !== q.answer) state.wrong[id] = 1;
  retry = false;
  save();
  stats();
  render();
  if (value === q.answer && state.autoNext && adjacent(1)) {
    advanceTimer = setTimeout(() => move(1), 750);
  }
}
$("autoNext").onchange = () => {
  state.autoNext = $("autoNext").checked;
  clearTimeout(advanceTimer);
  save();
};
$("question").addEventListener("click", (e) => {
  if (e.target.closest("summary")) clearTimeout(advanceTimer);
});
function move(step) {
  const next = adjacent(step);
  if (!next) return;
  if (state.mode === "wrong") state.wrongPos = next;
  else state.pos = next;
  load();
  window.scrollTo(0, 0);
}
$("prev").onclick = () => move(-1);
$("next").onclick = () => move(1);
const titles = { practice: "做题模式", study: "背题模式", wrong: "错题集" };
function route() {
  if (!m) return;
  clearTimeout(advanceTimer);
  ++revision;
  const mode = location.hash.slice(1);
  const inside = Object.hasOwn(titles, mode);
  $("home").hidden = inside;
  $("session").hidden = $("catalog").hidden = $("homeButton").hidden = !inside;
  $("modeTitle").textContent = inside ? titles[mode] : "练习室";
  if ($("drawer").open) $("drawer").close();
  if (inside) {
    state.mode = mode;
    $("autoLabel").hidden = mode === "study";
    $("autoNext").checked = state.autoNext;
    load();
  } else {
    stats();
    save();
  }
}
window.addEventListener("hashchange", route);
$("homeButton").onclick = () => {
  location.hash = "";
};
$("modes").onclick = (e) => {
  const mode = e.target.closest("button")?.dataset.mode;
  if (mode) location.hash = mode;
};
function jump(id) {
  if (state.mode === "wrong" && !state.wrong[id]) state.mode = "practice";
  if (state.mode === "wrong") state.wrongPos = id;
  else state.pos = id;
  $("drawer").close();
  if (location.hash.slice(1) !== state.mode) location.hash = state.mode;
  else load();
  window.scrollTo(0, 0);
}
const norm = (s) => s.normalize("NFKC").toLowerCase().replace(/\s/g, "");
function bucket(s) {
  let x = 0;
  for (const c of s) x = (x * 31 + c.codePointAt(0)) >>> 0;
  return x % 128;
}
function limits() {
  const b = m.books[Number($("books").value)];
  return b || { start: 1, end: m.total };
}
async function startDir(near = false) {
  const ticket = ++dirRev;
  page = 0;
  query = norm($("term").value);
  hits = [];
  scanned = 0;
  candidates = [];
  $("rows").replaceChildren();
  $("indexInfo").textContent = "正在查找…";
  $("indexPrev").disabled = $("indexNext").disabled = true;
  try {
    const { start, end } = limits();
    const prompt =
      start === 1 && end === m.total
        ? "搜索题干、选项或总题号"
        : "搜索题干、选项或本卷序号";
    $("term").placeholder = prompt;
    $("term").setAttribute("aria-label", prompt);
    if (/^\d+$/.test(query)) {
      const id = Number(query) + start - 1;
      if (id >= start && id <= end) hits = [id];
    } else if (query) {
      const chars = Array.from(query),
        grams =
          chars.length === 1
            ? chars
            : [...new Set(chars.slice(1).map((c, i) => chars[i] + c))];
      // 分段选取检索词，限制极长输入造成的索引请求数。
      const selected =
        grams.length <= 6
          ? grams
          : Array.from(
              { length: 6 },
              (_, i) => grams[Math.round((i * (grams.length - 1)) / 5)],
            );
      let matching = null;
      for (const gram of selected) {
        const d = await data(m.base + "/s" + bucket(gram) + ".json");
        if (ticket !== dirRev) return;
        let id = 0;
        const ids = (d[gram] || [])
          .map((delta) => (id += delta))
          .filter((n) => n >= start && n <= end);
        if (matching === null) matching = ids;
        else {
          const wanted = new Set(ids);
          matching = matching.filter((n) => wanted.has(n));
        }
        if (!matching.length) break;
      }
      candidates = matching || [];
    } else {
      hits = Array.from({ length: end - start + 1 }, (_, i) => start + i);
      if (near && current() >= start && current() <= end)
        page = Math.floor((current() - start) / 10);
    }
    await list(ticket);
  } catch {
    if (ticket === dirRev)
      $("rows").replaceChildren(button("目录载入失败，重试", () => startDir()));
  }
}
async function list(ticket) {
  const end = (page + 1) * 10;
  $("indexPrev").disabled = $("indexNext").disabled = true;
  while (hits.length <= end && scanned < candidates.length) {
    const id = candidates[scanned++],
      rec = await item(id);
    if (ticket !== dirRev) return;
    if (
      [rec.stem, ...Object.values(rec.options)].some((t) =>
        norm(t).includes(query),
      )
    )
      hits.push(id);
  }
  const visible = hits.slice(end - 10, end);
  const records = await Promise.all(visible.map(item));
  if (ticket !== dirRev) return;
  $("indexInfo").textContent = visible.length
    ? "第 " +
      (end - 9) +
      "–" +
      (end - 10 + visible.length) +
      " 项" +
      (scanned === candidates.length ? " / 共 " + hits.length + " 项" : "")
    : "未找到匹配题目";
  $("rows").replaceChildren();
  records.forEach((rec, i) => {
    const id = visible[i],
      b = button("", () => jump(id), "row");
    b.append(
      make("b", "#" + id),
      make("span", rec.stem),
      make(
        "em",
        state.wrong[id]
          ? "错题"
          : state.answers[id]
            ? "已答"
            : state.read[id]
              ? "已背"
              : !rec.answer
                ? "待核"
                : "",
      ),
    );
    $("rows").append(b);
  });
  $("indexPrev").disabled = !page;
  $("indexNext").disabled = hits.length <= end && scanned === candidates.length;
}
async function dirPage(delta) {
  page += delta;
  const ticket = ++dirRev;
  try {
    await list(ticket);
  } catch {
    if (ticket === dirRev)
      $("rows").replaceChildren(button("载入失败，重试", () => dirPage(0)));
  }
}
$("indexPrev").onclick = () => dirPage(-1);
$("indexNext").onclick = () => dirPage(1);
$("catalog").onclick = () => {
  if (!m) return;
  clearTimeout(advanceTimer);
  $("term").value = "";
  $("books").value = "-1";
  $("drawer").showModal();
  startDir(true);
};
$("close").onclick = () => $("drawer").close();
$("search").onsubmit = (e) => {
  e.preventDefault();
  startDir();
};
$("books").onchange = () => startDir();
async function init() {
  try {
    m = await data("manifest.json");
    heldBits = atob(m.held || "");
    for (const id of Object.keys(state.answers)) {
      if (!book(+id) || isHeld(+id)) {
        delete state.answers[id];
        delete state.wrong[id];
      }
    }
    $("books").add(new Option("全部题库", "-1"));
    m.books.forEach((b, i) => $("books").add(new Option(b.name, i)));
    if (!book(state.pos)) state.pos = 1;
    $("homeError").replaceChildren();
    route();
  } catch {
    $("homeError").replaceChildren(button("题库载入失败，点击重试", init));
  }
}
init();
