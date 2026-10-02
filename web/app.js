import { setupInteractions } from './interactions.js?v=e4fc21dfa5c3834c';
import { verifyGrant, decryptContent, shortCodeAddress, unwrapGrant, MAX_BYTES } from './crypto.js?v=535278c2f036bf31';

const form = document.querySelector('#access-form');
const input = document.querySelector('#access-code');
const unlock = document.querySelector('#unlock-button');
const message = document.querySelector('#access-message');
const access = document.querySelector('#access');
const portfolio = document.querySelector('#portfolio');
const container = document.querySelector('#portfolio-content');
const { isComposing } = setupInteractions(document);
const urls = new Set();
let expires = 0;
let expiryTimer;
let operation = 0;
let controller;

function element(tag, className, text) {
  const node = document.createElement(tag);
  if (className) node.className = className;
  if (text !== undefined) node.textContent = text;
  return node;
}
function bulletList(items, className = '') {
  const list = element('ul', className);
  for (const text of items ?? []) list.append(element('li', '', text));
  return list;
}
function announce(text, error = false) {
  message.textContent = text;
  message.classList.toggle('error', error);
}
function lock(text = '', focus = false) {
  operation++;
  controller?.abort();
  clearTimeout(expiryTimer);
  expires = 0;
  container.replaceChildren();
  for (const url of urls) URL.revokeObjectURL(url);
  urls.clear();
  portfolio.hidden = true;
  access.hidden = false;
  input.value = '';
  unlock.disabled = false;
  unlock.textContent = '解锁项目 →';
  announce(text);
  if (focus) input.focus({ preventScroll: true });
}
function watchExpiry() {
  clearTimeout(expiryTimer);
  if (!expires) return;
  const remaining = expires * 1000 - Date.now();
  if (remaining <= 0) { lock('授权已到期，项目详情已收起。请向分享者索取新的授权码。', true); return; }
  expiryTimer = setTimeout(watchExpiry, Math.min(remaining, 60000));
}
function renderMedia(media) {
  if (!['image/png', 'image/gif', 'image/webp'].includes(media.mime) || !/^[A-Za-z0-9+/]*={0,2}$/.test(media.data)) throw new Error('素材格式不受支持。');
  const bytes = Uint8Array.from(atob(media.data), c => c.charCodeAt(0));
  const url = URL.createObjectURL(new Blob([bytes], { type: media.mime }));
  urls.add(url);
  const figure = element('figure', 'project-media');
  const img = element('img');
  img.alt = media.alt;
  img.loading = 'lazy'; img.decoding = 'async';
  if (media.mime === 'image/png') { img.src = url; figure.append(img); }
  else {
    // 动图只在用户明确点击后加载；停止时移除源，避免后台继续播放。
    const button = element('button', 'media-button', `查看演示 · ${media.alt}`);
    button.type = 'button'; button.setAttribute('aria-expanded', 'false');
    button.addEventListener('click', () => {
      if (img.isConnected) {
        img.remove(); img.removeAttribute('src'); button.textContent = `查看演示 · ${media.alt}`;
        button.setAttribute('aria-expanded', 'false');
      } else {
        img.src = url; figure.prepend(img); button.textContent = '停止并收起演示';
        button.setAttribute('aria-expanded', 'true');
      }
    });
    figure.append(button);
  }
  if (media.caption) figure.append(element('figcaption', '', media.caption));
  return figure;
}
function render(content) {
  const fragment = document.createDocumentFragment();
  const intro = element('div', 'portfolio-intro');
  intro.append(element('p', 'eyebrow', 'SELECTED WORK / 项目与实践'));
  const title = element('h2', '', content.headline); title.id = 'portfolio-title'; title.tabIndex = -1;
  intro.append(title, element('p', '', content.intro), bulletList(content.strengths, 'strengths'));
  fragment.append(intro);
  const nav = element('nav', 'project-nav'); nav.setAttribute('aria-label', '项目目录');
  content.projects.forEach((project, i) => {
    const link = element('a', '', `${String(i + 1).padStart(2, '0')} · ${project.title}`);
    link.href = `#project-${project.id}`; nav.append(link);
  });
  fragment.append(nav);
  content.projects.forEach((project, i) => {
    const card = element('article', 'project-card'); card.id = `project-${project.id}`;
    const topline = element('div', 'project-topline');
    topline.append(element('p', 'eyebrow', project.category), element('span', 'project-number', String(i + 1).padStart(2, '0')));
    card.append(topline, element('h3', '', project.title), element('p', 'project-summary', project.summary), bulletList(project.tags, 'tags'));
    const body = element('div', 'project-body');
    const challenge = element('div'); challenge.append(element('h4', '', '面对的问题'), element('p', '', project.challenge));
    const approach = element('div'); approach.append(element('h4', '', '我的方案与贡献'), bulletList(project.approach));
    body.append(challenge, approach); card.append(body);
    const results = element('div', 'project-results'); results.append(element('h4', '', '实践结果'), bulletList(project.outcomes)); card.append(results);
    if (project.media?.length) {
      const gallery = element('div', 'media-grid');
      project.media.forEach(media => gallery.append(renderMedia(media))); card.append(gallery);
    }
    fragment.append(card);
  });
  if (content.experience?.length) {
    const experience = element('section', 'experience-section'); experience.append(element('h2', '', '经历中的积累'));
    const list = element('div', 'experience-list');
    content.experience.forEach(item => {
      const row = element('article', 'experience-item'); const detail = element('div');
      detail.append(element('h3', '', item.title), element('p', '', item.description));
      row.append(element('time', '', item.period), detail); list.append(row);
    });
    experience.append(list); fragment.append(experience);
  }
  fragment.append(bulletList(content.skills, 'tags'));
  if (content.note) fragment.append(element('p', 'portfolio-note', content.note));
  container.replaceChildren(fragment);
}
async function fetchBytes(url, limit, signal, cache = 'no-store') {
  const response = await fetch(url, { cache, signal, credentials: 'omit', referrerPolicy: 'no-referrer' });
  if (!response.ok) throw new Error(url.startsWith('./content/grants/') ? '未找到这份授权，请检查授权码或确认分享者已发布。' : '展示文件暂时不可用，请稍后重试或联系分享者。');
  const reader = response.body.getReader();
  const chunks = []; let total = 0;
  while (true) {
    const { value, done } = await reader.read(); if (done) break;
    total += value.byteLength;
    if (total > limit) { await reader.cancel(); throw new Error('展示文件过大，无法加载。'); }
    chunks.push(value);
  }
  const bytes = new Uint8Array(total); let offset = 0;
  for (const chunk of chunks) { bytes.set(chunk, offset); offset += chunk.length; }
  return bytes;
}
form.addEventListener('submit', async event => {
  event.preventDefault();
  if (isComposing() || unlock.disabled) return;
  if (!crypto?.subtle) { announce('请通过 HTTPS 网站或 localhost 打开页面，当前环境无法使用加密功能。', true); return; }
  let token = input.value.trim();
  const current = ++operation;
  controller?.abort(); controller = new AbortController();
  const requestController = controller;
  const timeout = setTimeout(() => requestController.abort(), 30000);
  unlock.disabled = true; unlock.textContent = '正在校验…'; announce('正在校验授权并加载项目。');
  try {
    if (!token.startsWith('cr1.')) {
      const address = await shortCodeAddress(token);
      const envelope = await fetchBytes(`./content/grants/${address}.bin`, 8192, requestController.signal);
      token = await unwrapGrant(token, envelope);
    }
    const keyring = JSON.parse(new TextDecoder().decode(await fetchBytes('./content/keys.json', 65536, requestController.signal)));
    const grant = await verifyGrant(token, keyring);
    unlock.textContent = '正在解锁…';
    const bytes = await fetchBytes('./content/latest.bin', MAX_BYTES, requestController.signal, 'no-store');
    const content = await decryptContent(grant, bytes);
    if (current !== operation) return;
    if (Date.now() >= grant.exp * 1000) throw new Error('授权已到期，请向分享者索取新的授权码。');
    render(content);
    expires = grant.exp;
    input.value = '';
    document.querySelector('#expires-label').textContent = `有效至 ${new Date(expires * 1000).toLocaleString('zh-CN', { timeZoneName: 'short' })}`;
    access.hidden = true; portfolio.hidden = false;
    announce('');
    watchExpiry();
    document.querySelector('#portfolio-title').focus({ preventScroll: true });
    portfolio.scrollIntoView({ behavior: matchMedia('(prefers-reduced-motion: reduce)').matches ? 'instant' : 'smooth' });
  } catch (error) {
    if (current !== operation) return;
    lock();
    announce(error.name === 'AbortError' ? '加载超时，请检查网络后重试。' : error instanceof TypeError ? '网络连接失败，请稍后重试。' : error.message, true);
  } finally {
    clearTimeout(timeout);
    if (current === operation) { unlock.disabled = false; unlock.textContent = '解锁项目 →'; }
  }
});
document.querySelector('#lock-button').addEventListener('click', () => { lock('项目详情已锁定。', true); access.scrollIntoView(); });
document.querySelectorAll('a[href="#access"]').forEach(link => {
  link.addEventListener('click', event => {
    if (!portfolio.hidden) {
      event.preventDefault();
      portfolio.scrollIntoView();
      document.querySelector('#portfolio-title').focus({ preventScroll: true });
    }
  });
});
document.addEventListener('visibilitychange', () => { if (!document.hidden) watchExpiry(); });
window.addEventListener('pagehide', () => lock());
window.addEventListener('pageshow', watchExpiry);
// 片段不作为 HTTP 请求参数发送；读取后立即从地址栏移除，仍需主动提交解锁。
function readAccessFragment() {
  if (!location.hash.startsWith('#access=')) return;
  const token = location.hash.slice(8, 4104);
  history.replaceState(null, '', location.pathname + location.search);
  lock();
  input.value = token;
  announce('已填入授权码，按回车或点击“解锁项目”即可查看。');
  access.scrollIntoView();
}
window.addEventListener('hashchange', readAccessFragment);
readAccessFragment();
