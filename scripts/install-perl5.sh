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

make_perl_url() {
    #echo "https://codeload.github.com/Perl/perl5/tar.gz/v$1"
    echo "http://www.cpan.org/src/5.0/perl-$1.tar.gz"
}

make_perl_file_name() {
    echo "perl-$1"
}

case "$version" in
    # v5.26
    5.26.0|5.26.1|5.26.2)
        perl_file_name=$(make_perl_file_name $version)
        ;;
    *)
        ;;
esac

if [ "$perl_file_name" = "" ]; then
    _error "Perl v$version not found!"
    exit 1
fi

pwd=$(pwd)
perl_dir_name=$perl_file_name
perl_file_name="$perl_file_name.tar.gz"
perl_url=$(make_perl_url $version $perl_file_name)
perl_file_path="$download_path/$perl_file_name"
perl_dir_path="$download_path/$perl_dir_name"
perl_bin_folder_path="$install_path/bin"
perl_bin_path="$perl_bin_folder_path/perl"
perl_bin_path_with_version="$perl_bin_folder_path/perl$version"

echo "pwd: $pwd"
echo "perl_dir_name: $perl_dir_name"
echo "perl_file_name: $perl_file_name"
echo "perl_url: $perl_url"
echo "perl_file_path: $perl_file_path"
echo "perl_dir_path: $perl_dir_path"
echo "perl_bin_folder_path: $perl_bin_folder_path"
echo "perl_bin_path: $perl_bin_path"

if [ ! -d $install_path ]; then
    mkdir $install_path -p
fi

echo "Installing Perl v$version..."
echo "-----------------------------"

if [ ! -f $perl_file_path ]; then
    echo " -> Downloading $perl_url..."
    download $perl_url $perl_file_path
fi

if [ ! -d $perl_dir_path ]; then
    echo " -> Extracting $perl_file_name"
    extract_zipfile $perl_file_path $download_path
fi

echo " -> Building source (this may take a while)..."
cd $perl_dir_path
use_threads=-Dusethreads
use_64bit=-Duse64bitall
if [ $is_x86 = true ]; then
    use_64bit=
fi
sh Configure -de -Dusedevel $use_threads $use_64bit -Dprefix=$install_path
make install PERLNAME=perl5 PERLNAME_VERBASE=perl
cd $pwd

# if [ "$?" = "0" ]; then
#     echo " -> Removing temporary files..."
#     rm -Rf $perl_file_path
#     rm -Rdf $perl_dir_path
# fi

if [ ! -f $perl_bin_path ]; then
    _error "Perl v$version install fail!"
    exit 1
fi

echo "-----------------------------"
echo "Perl v$version successfully install!"
echo ""
