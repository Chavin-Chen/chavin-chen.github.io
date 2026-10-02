export function setupInteractions(doc) {
  const toggle = doc.querySelector('#theme-toggle');
  const field = doc.querySelector('#access-code');
  const form = doc.querySelector('#access-form');
  const submit = doc.querySelector('#unlock-button');
  let composing = false;
  let compositionEnded = -Infinity;
  toggle.addEventListener('click', () => {
    const dark = doc.documentElement.dataset.theme !== 'dark';
    doc.documentElement.dataset.theme = dark ? 'dark' : 'light';
    toggle.setAttribute('title', dark ? '切换到浅色模式' : '切换到深色模式');
    toggle.setAttribute('aria-checked', String(dark));
    doc.querySelector('meta[name="theme-color"]').setAttribute('content', dark ? '#111b17' : '#f7f9f6');
  });
  field.addEventListener('compositionstart', () => { composing = true; });
  field.addEventListener('compositionend', () => {
    composing = false;
    compositionEnded = performance.now();
  });
  const isComposing = () => composing || performance.now() - compositionEnded < 100;
  field.addEventListener('keydown', event => {
    if (event.key !== 'Enter') return;
    // 部分手机输入法会先结束 composition 再发 Enter；确认候选词时不提交。
    if (event.isComposing || event.keyCode === 229 || isComposing()) {
      if (!event.isComposing && !composing) event.preventDefault();
      return;
    }
    event.preventDefault();
    if (!event.repeat && !submit.disabled) form.requestSubmit(submit);
  });
  return { isComposing };
}
