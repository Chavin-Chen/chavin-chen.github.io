const encoder = new TextEncoder();
export const AUDIENCE = 'chavin-portfolio';
export const MAX_BYTES = 32 * 1024 * 1024;

export function decode64(value) {
  if (typeof value !== 'string' || !/^[A-Za-z0-9_-]+$/.test(value)) throw new Error('授权码格式不正确。');
  return Uint8Array.from(atob(value.replace(/-/g, '+').replace(/_/g, '/')), c => c.charCodeAt(0));
}

export function checkTime(grant, now = Date.now()) {
  const seconds = Math.floor(now / 1000);
  if (![grant.iat, grant.nbf, grant.exp].every(Number.isSafeInteger) || grant.exp <= grant.nbf || grant.iat > grant.exp) {
    throw new Error('授权时间格式不正确。');
  }
  if (seconds < grant.nbf) throw new Error('授权尚未生效，请在约定时间访问。');
  if (seconds >= grant.exp) throw new Error('授权已到期，请向分享者索取新的授权码。');
}

export async function verifyGrant(token, keyring, now = Date.now()) {
  if (typeof token !== 'string' || token.length > 4096) throw new Error('授权码格式不正确。');
  const parts = token.trim().split('.');
  if (parts.length !== 3 || parts[0] !== 'cr1') throw new Error('请粘贴完整的授权码。');
  let grant;
  try { grant = JSON.parse(new TextDecoder().decode(decode64(parts[1]))); }
  catch { throw new Error('授权码格式不正确。'); }
  if (!grant || grant.v !== 2 || grant.aud !== AUDIENCE ||
      !/^[a-f0-9]{32}$/.test(grant.jti) ||
      !/^[a-f0-9]{24}$/.test(grant.kid) || decode64(grant.key).length !== 32) {
    throw new Error('授权码内容不完整或不适用于此网站。');
  }
  if (keyring?.v !== 1 || !Object.hasOwn(keyring.keys ?? {}, grant.kid)) throw new Error('暂不支持这份授权，请联系分享者。');
  const jwk = keyring.keys[grant.kid];
  if (jwk.kty !== 'EC' || jwk.crv !== 'P-256' || jwk.d) throw new Error('网站公钥配置不正确。');
  const key = await crypto.subtle.importKey('jwk', jwk, { name: 'ECDSA', namedCurve: 'P-256' }, false, ['verify']);
  const valid = await crypto.subtle.verify({ name: 'ECDSA', hash: 'SHA-256' }, key,
    decode64(parts[2]), encoder.encode(`cr1.${parts[1]}`));
  if (!valid) throw new Error('授权码校验失败，请确认复制完整且未被修改。');
  checkTime(grant, now);
  return grant;
}

export async function decryptContent(grant, bytes) {
  if (bytes.byteLength < 29 || bytes.byteLength > MAX_BYTES) throw new Error('展示内容大小不正确。');
  const key = await crypto.subtle.importKey('raw', decode64(grant.key), 'AES-GCM', false, ['decrypt']);
  let plain;
  try {
    plain = await crypto.subtle.decrypt({ name: 'AES-GCM', iv: bytes.slice(0, 12),
      additionalData: encoder.encode('chavin-resume:latest:v1'), tagLength: 128 }, key, bytes.slice(12));
  } catch { throw new Error('无法解密展示内容，请联系分享者。'); }
  const content = JSON.parse(new TextDecoder().decode(plain));
  if (content.schema !== 1 || !Array.isArray(content.projects)) throw new Error('展示内容格式不受支持。');
  return content;
}


// 地址与加密密钥采用不同的域分隔，公开文件名不能直接用于解密。
export async function shortCodeAddress(value) {
  const code = value.trim().toLowerCase();
  if (!/^[a-f0-9]{32}$/.test(code)) throw new Error('请输入完整的授权码。');
  const digest = new Uint8Array(await crypto.subtle.digest('SHA-256', encoder.encode(`chavin-grant:lookup:v1:${code}`)));
  return Array.from(digest, b => b.toString(16).padStart(2, '0')).join('');
}

export async function unwrapGrant(value, bytes) {
  const code = value.trim().toLowerCase();
  const address = await shortCodeAddress(code);
  if (bytes.byteLength < 29 || bytes.byteLength > 8192) throw new Error('授权文件格式不正确。');
  const material = await crypto.subtle.digest('SHA-256', encoder.encode(`chavin-grant:wrap:v1:${code}`));
  const key = await crypto.subtle.importKey('raw', material, 'AES-GCM', false, ['decrypt']);
  try {
    const plain = await crypto.subtle.decrypt({ name: 'AES-GCM', iv: bytes.slice(0, 12),
      additionalData: encoder.encode(`chavin-grant:v1:${address}`), tagLength: 128 }, key, bytes.slice(12));
    return new TextDecoder().decode(plain);
  } catch { throw new Error('授权码不正确或授权文件已损坏。'); }
}
