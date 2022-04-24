import { readFileSync } from 'fs';
import { BMPdecode, BMPencode } from '../src';
import { images } from './resources/image.json';

describe('Encode rgb to bmp files', () => {
  for (const { name, width, height, channels } of images) {
    test(`Encoding ${name}.rgb to ${name}.bmp`, () => {
      const raw = readFileSync(`./test/resources/out_rgb/${name}.rgb`);
      const bmp = readFileSync(`./test/resources/out_bmp/${name}.bmp`);

      const result = BMPencode(raw, {
        channels,
        width,
        height,
      });

      expect(result instanceof Buffer).toBe(true);

      expect(result.equals(bmp)).toBe(true);
    });
  }
});

describe('Encode bmp to rgb files', () => {
  for (const { name, width, height, channels } of images) {
    test(`Encoding ${name}.bmp to ${name}.rgb`, () => {
      const bmp = readFileSync(`./test/resources/in_bmp/${name}.bmp`);
      const raw = readFileSync(`./test/resources/out_rgb/${name}.rgb`);

      const result = BMPdecode(bmp);

      expect(typeof result).toBe('object');

      expect(result.channels).toBe(channels);
      expect(result.width).toBe(width);
      expect(result.height).toBe(height);

      expect(result.pixels instanceof Buffer).toBe(true);

      expect(result.pixels.equals(raw)).toBe(true);
    });
  }
});
