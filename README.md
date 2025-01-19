# RLC4.0

## Usage

```shell
RLC40 /path/to/param.cfg
```

## Configuration File Format

### Generic Options

| option          | type   | description                                                                                  |
|-----------------|--------|----------------------------------------------------------------------------------------------|
| method          | int    | The rendering method is provided by TLCT v0.12.0 (0), v0.15.0 (1) or v0.15.2.0 (2)           |
| Calibration_xml | string | The path of the calibration file                                                             |
| RawImage_Path   | string | The glob pattern of the input images in C-printf style, will be filled with the frame index  |
| Output_Path     | string | The glob pattern of the output images in C-printf style, will be filled with the frame index |
| start_frame     | int    | The index of the start frame, left contains                                                  |
| end_frame       | int    | The index of the end frame, right contains                                                   |
| width           | int    | The pixel width of input image                                                               |
| height          | int    | The pixel height of input image                                                              |

### Fine-tune Options

All fine-tune options are optional

| option                 | type  | description                                                                                    | recommend | default |
|------------------------|-------|------------------------------------------------------------------------------------------------|-----------|---------|
| upsample               | int   | The input image will be upsampled by this scale                                                | 2~4       | 2       |
| psizeInflate           | float | The extracted patch will be inflated by this scale                                             | 1.5~3     | 2.15    |
| maxPsize               | float | Patch size will never be larger than `maxPsize*diameter`                                       | 0.3~1.0   | 0.5     |
| patternSize            | float | The size of matching pattern will be `patternSize*diameter`                                    | 0.25~0.4  | 0.3     |
| psizeShortcutThreshold | int   | If the difference bit of dhash of MI is smaller than this value, then use the prev. patch size | 2~8       | 4       |

### Example of param.cfg

```
pipeline                1
Calibration_xml         Boys.xml
RawImage_Path           Boys/src/Image%03d.png
Output_Path             Boys/dst/frame%03d
start_frame             1
end_frame               300
height                  2048
width                   2048
upsample                2
psizeInflate            2.0
maxPsize                0.5
patternSize             0.3
psizeShortcutThreshold  4
```

### Charset

Must be utf-8

## Compiling

### Dependencies

1. CMake with version of at least 3.15.
2. OpenCV 4.9 or above, with the [OpenCV contrib module quality](https://github.com/opencv/opencv_contrib/tree/4.x/modules/quality)
3. [pugixml](https://pugixml.org) to read XML files.
4. RLC4.0 can be complied by MSVC 19.39, GCC 13 or Clang 18.

The recommended Dockerfile:

```dockerfile
FROM silkeh/clang:19 AS builder

RUN apt update && \
    apt install -y --no-install-recommends git && \
    apt clean

# OpenCV
ARG OPENCV_VER=4.10.0

ADD opencv-${OPENCV_VER}.tar.xz ./
ADD opencv_contrib-${OPENCV_VER}.tar.xz ./
RUN cd opencv-${OPENCV_VER} && \
    cmake -S . -B build -DBUILD_LIST="imgcodecs,imgproc,quality" -DBUILD_SHARED_LIBS=OFF -DCV_TRACE=OFF -DCPU_BASELINE=AVX2 -DCPU_DISPATCH=AVX2 -DOPENCV_ENABLE_ALLOCATOR_STATS=OFF -DWITH_ADE=OFF -DWITH_DSHOW=OFF -DWITH_FFMPEG=OFF -DWITH_IMGCODEC_HDR=OFF -DWITH_IMGCODEC_PFM=OFF -DWITH_IMGCODEC_PXM=OFF -DWITH_IMGCODEC_SUNRASTER=OFF -DWITH_IPP=OFF -DWITH_ITT=OFF -DWITH_JASPER=OFF -DWITH_JPEG=OFF -DWITH_LAPACK=OFF -DWITH_OPENCL=OFF -DWITH_OPENEXR=OFF -DWITH_OPENJPEG=OFF -DWITH_PROTOBUF=OFF -DWITH_TIFF=OFF -DWITH_WEBP=OFF -DOPENCV_EXTRA_MODULES_PATH=/opencv_contrib-${OPENCV_VER}/modules && \
    make -C build -j$($(nproc)-1) && \
    make -C build install

# RLC
ADD RLC40-master.tar.xz ./
RUN cd RLC40-master && \
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --config Release --parallel $($(nproc)-1) --target RLC40


FROM debian:12-slim AS prod

COPY --from=builder RLC40-master/build/RLC40 /usr/bin

CMD ["bash"]
```
