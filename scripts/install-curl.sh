#!/bin/sh

_has() {
    type "${1}" > /dev/null 2>&1
}

_os()
{
    local uname=`uname`
    if [ ${uname} = "Darwin" ]; then
        echo "darwin"
    elif [ ${uname} = "FreeBSD" ]; then
        echo "freebsd"
    elif [ ${uname} = "Linux" ]; then
        echo "linux"
    else
        echo "other"
    fi
}

_error()
{
    echo "Error: ${1}"
}

# -----------------
# Script parameters
# -----------------
while [ $# -ne 0 ]
do
    name="$1"
    case "$name" in
        --version|-[Vv]ersion)
            shift
            version="$1"
            ;;
        --[Ii]nstall-[Pp]ath)
            shift
            install_path="$1"
            ;;
        --[Dd]ownload-[Pp]ath)
            shift
            download_path="$1"
            ;;
        --[Bb]uild-[Ss]tatic)
            build_static=true
            ;;
        --[Bb]uild-[Ee]xe)
            build_exe=true
            ;;
        *)
            _error "Unknown argument \`$name\`"
            exit 1
            ;;
    esac

    shift
done

# -------------------
# Check prerequisites
# -------------------
if ! _has "uname"; then
    _error "Unix uname is required"
    exit 1
fi

#if [ ! `_os` = "linux" ] && [ ! `_os` = "darwin" ]; then
if [ ! `_os` = "linux" ]; then
    _error "OS "`_os`" is not supported"
    exit 1
fi

if ! _has "tar"; then
    _error "Unix tar is required"
    exit 1
fi

if ! _has "curl" && ! _has "wget" && ! _has "fetch"; then
    _error "Tool curl, wget or fetch is required"
    exit 1
fi

if ! _has "cmake"; then
    _error "CMake is required"
    exit 1
fi

if ! _has "make"; then
    _error "Unix make is required"
    exit 1
fi

if [ "$version" = "" ]; then
    _error "--version is required."
    exit 1
fi

if [ "$install_path" = "" ]; then
    _error "--install-path is required."
    exit 1
fi

if [ "$download_path" = "" ]; then
    download_path=$install_path
fi

arch=`uname -m`

x86_linux_arch="i386"
x64_linux_arch="x86_64"
is_x86=true
linux_arch=$x86_linux_arch

if [ "$arch" = "x86_64" ] || [ "$arch" = "x64" ]; then
    linux_arch=$x64_linux_arch
    is_x86=false
fi

extract_zipfile()
{
    local zip_path="$1"
    local out_path="$2"

    tar -xzf "$zip_path" -C "$out_path" > /dev/null
}

download() {
    local url="$1"
    local path="${2:-}"
    
    if _has "curl"; then
        downloadcurl "$url" "$path"
    elif _has "wget"; then
        downloadwget "$url" "$path"
    else
        _error "fetch download not implemented"
    fi
}

downloadcurl() {
    local url="$1"
    local path="${2:-}"

    curl --retry 10 -sSL -f --create-dirs -o "$path" "$url"
}

downloadwget() {
    local url="$1"
    local path="${2:-}"

    wget --tries 10 -O "$path" "$url"
}

make_curl_url() {
    # mirror: Canada (Vancouver)                -> https://curl.mirror.anstey.ca/{0}
    # mirror: Canada (Fastly (worldwide))       -> https://curl.haxx.se/download/{0}
    # mirror: Germany (St. Wendel, Saarland)    -> https://dl.uxnr.de/mirror/curl/{0}
    # mirror: Singapore                         -> https://execve.net/mirror/curl/{0}
    # mirror: US (Houston, Texas)               -> https://curl.askapache.com/{0}
    echo "https://curl.askapache.com/$1"
}

make_curl_file_name() {
    echo "curl-$1"
}

case "$version" in
    7.20.0|7.20.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.21.0|7.21.1|7.21.2|7.21.3|7.21.4|7.21.5|7.21.6|7.21.7)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.22.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.23.0|7.23.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.24.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.25.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.26.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.27.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.28.0|7.28.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.29.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.30.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.31.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.32.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.33.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.34.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.35.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.36.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.37.0|7.37.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.38.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.39.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.40.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.41.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.42.0|7.42.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.43.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.44.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.45.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.46.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.47.0|7.47.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.48.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.49.0|7.49.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.50.0|7.50.1|7.50.2|7.50.3)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.51.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.52.0|7.52.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.53.0|7.53.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.54.0|7.54.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.55.0|7.55.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.56.0|7.56.1)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.57.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.58.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.59.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
	7.60.0)
        curl_file_name=$(make_curl_file_name $version)
        ;;
    *)
        ;;
esac

if [ "$curl_file_name" = "" ]; then
    _error "CURL v$version not found!"
    exit 1
fi

pwd=$(pwd)
curl_dir_name=$curl_file_name
curl_file_name="$curl_file_name.tar.gz"
curl_url=$(make_curl_url $curl_file_name)
curl_file_path="$download_path/$curl_file_name"
curl_dir_path="$download_path/$curl_dir_name"
curl_bin_folder_path="$install_path/bin"
curl_bin_path="$curl_bin_folder_path/curl"
curl_build_path="$curl_dir_path/build"

echo "pwd = $pwd"
echo "curl_dir_name = $curl_dir_name"
echo "curl_file_name = $curl_file_name"
echo "curl_url = $curl_url"
echo "curl_file_path = $curl_file_path"
echo "curl_dir_path = $curl_dir_path"
echo "curl_bin_folder_path = $curl_bin_folder_path"
echo "curl_bin_path = $curl_bin_path"
echo "curl_build_path = $curl_build_path"

if [ ! -d $install_path ]; then
    mkdir $install_path -p
fi

echo "Installing CURL v$version..."
echo "-----------------------------"

if [ ! -f $curl_file_path ]; then
    echo " -> Downloading $curl_url..."
    download $curl_url $curl_file_path
fi

if [ ! -d $curl_dir_path ]; then
    echo " -> Extracting $curl_file_name"
    extract_zipfile $curl_file_path $download_path
fi

if [ -d $curl_dir_path ]; then
    echo " -> Building source (this may take a while)..."

    if [ ! -d $curl_build_path ]; then
        mkdir -p $curl_build_path
    fi

    if [ $build_exe = true ]; then
        build_exe_param="BUILD_CURL_EXE=ON"
    else
        build_exe_param="BUILD_CURL_EXE=OFF"
    fi

    if [ $build_static = true ]; then
        build_static_param="CURL_STATICLIB=ON"
    else
        build_static_param="CURL_STATICLIB=OFF"
    fi

    cd $curl_build_path

    cmake -G "Unix Makefiles" $curl_dir_path \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_INSTALL_PREFIX=$install_path \
      -D$build_exe_param \
      -D$build_static_param \
      -DHTTP_ONLY=ON \
      -DCURL_CA_PATH=none \
      -DCMAKE_USE_OPENSSL=OFF \
      -DCURL_ZLIB=OFF \
	  -DBUILD_TESTING=OFF

    if [ "$?" = "0" ]; then
	    make install
    fi
    
    cd $pwd
fi

if [ "$?" = "0" ]; then
    echo " -> Removing temporary files..."
    rm -Rf $curl_file_path
    rm -Rdf $curl_dir_path
fi

if [ ! -f $curl_bin_path ]; then
    _error "CURL v$version install fail!"
    exit 1
fi

echo "-----------------------------"
echo "CURL v$version successfully install!"
echo ""
