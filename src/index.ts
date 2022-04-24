export enum BMPChannels {
  RGB = 3,
  RGBA = 4,
}

type addonType = {
  encode: (
    pixels: Buffer,
    width: number,
    height: number,
    channels: BMPChannels,
  ) => Buffer;
  decode: (data: Buffer) => {
    pixels: Buffer;
    width: number;
    height: number;
    channels: BMPChannels;
  };
};

const addon = require('bindings')('bmpxx_addon') as addonType;

export function BMPencode(
  pixels: Buffer,
  options: {
    width: number;
    height: number;
    channels: BMPChannels;
  },
): Buffer {
  return addon.encode(pixels, options.width, options.height, options.channels);
}

export function BMPdecode(data: Buffer): {
  pixels: Buffer;
  width: number;
  height: number;
  channels: BMPChannels;
} {
  return addon.decode(data);
}
