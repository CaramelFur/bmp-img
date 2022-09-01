# bmp-img

Typescript bindings for encoding and decoding BMP images.
This library uses the [BMPxx](https://github.com/rubikscraft/BMPxx) c++ library.

## Documentation

### Encoding

You can encode a BMP image with the `BMPencode` function.
The input pixels are ordered as either `RGB` or `RGBA`, depending on what you specify in the channels parameter.

```js
function BMPencode(
  pixels: Buffer,
  options: {
    width: number;
    height: number;
    channels: BMPChannels;
  },
) => Buffer
```

### Decoding

Decoding is just as easy. You can decode an image by using the `BMPdecode` function.
The output pixels are ordered as either `RGB` or `RGBA`, depending on the channels value.

```js
function BMPdecode(data: Buffer) => {
  pixels: Buffer;
  width: number;
  height: number;
  channels: BMPChannels;
}
```

### Enums

```js
enum BMPChannels {
  RGB = 3,
  RGBA = 4,
}
```

## Release notes

* [v1.2.0]
  * Update dependencies
  * Remove building with `-march=native`
* [v1.1.0]
  * Update BMPxx
* [v1.0.0]
  * Initial release
