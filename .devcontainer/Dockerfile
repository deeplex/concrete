FROM mcr.microsoft.com/devcontainers/base:ubuntu-22.04
USER root

RUN apt-get -y update && apt-get -y install --no-install-recommends \
        build-essential \
        clang-15 \
        cmake \
        curl \
        git \
        lldb-15 \
        llvm-15-dev \
        lzma-dev \
        gdb \
        ninja-build \
        python3 \
        unzip \
        zip \
    && apt-get -y autoremove && apt-get -y clean && rm -rf /var/lib/apt/lists/* &&\
    update-alternatives --install /usr/bin/clang clang /usr/bin/clang-15 150 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-15

# Setup ENV vars for vcpkg
ENV VCPKG_ROOT=/opt/vcpkg \
    VCPKG_DOWNLOADS=$XDG_CACHE_HOME/vcpkg/downloads \
    VCPKG_DEFAULT_BINARY_CACHE=$XDG_CACHE_HOME/vcpkg/archives

RUN mkdir -p "${VCPKG_ROOT}" \
 && chmod 0775 "${VCPKG_ROOT}" \
 && chown vscode:vscode "${VCPKG_ROOT}"

USER vscode
RUN mkdir -p "${VCPKG_DOWNLOADS}" "${VCPKG_DEFAULT_BINARY_CACHE}" \
 &&  git clone --shallow-since="1 year" \
    -c core.eol=lf \
    -c core.autocrlf=false \
    -c fsck.zeroPaddedFilemode=ignore \
    -c fetch.fsck.zeroPaddedFilemode=ignore \
    -c receive.fsck.zeroPaddedFilemode=ignore \
    https://github.com/microsoft/vcpkg "${VCPKG_ROOT}" \
 && "${VCPKG_ROOT}"/bootstrap-vcpkg.sh
