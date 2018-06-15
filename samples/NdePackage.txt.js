package({
    ID: "mypkg",
    DESCRIPTION: "MyPkg package for NDE",
    AUTHOR: "Erlimar",
    AUTHOR_CONTACT: [
        "twitter:@erlimar",
        "email:erlimar@gmail.com",
        "github:erlimar"
    ],
    OWNER: "Dono original do MyPkg",
    LICENSE: "MIT",
    LICENSE_URL: "https://license.url",
    TAGS: [
        "net",
        "http",
        "internet",
        "transfer"
    ]
})

var ON = true
var OFF = false
var BOOLEAN_LIST = [ON, OFF]

// $ nde.. --OPTION_A "value to option a"
// $ nde.. --OPTION_A = "value to option a"
option("OPTION_A", "*", { required: true })

// $ nde.. --USE_STATIC--USE_ZLIB
// $ nde.. --USE - STATIC--USE - ZLIB
// $ nde.. --use_static--use_zlib
//# $ nde.. --use - static--use - zlib
option("USE_STATIC", OFF, { accepted: BOOLEAN_LIST })
option("USE_ZLIB", ON, { accepted: BOOLEAN_LIST })

// = Garante PATCH como versão mínima
// ~Garante MINOR como versão mínima
// ^ Garante MAJOR como versão mínima
// { id } { min_version } [..{ max_version }]
require("zlib", "~1.45", function (zlib, ignore) {
    if (!option("USE_ZLIB"))
        ignore();

    zlib.options({
        OPTION_A: "OPTION A VALUE",
        OPTION_B: "OPTION_B_VALUE",
        USE_STATIC: option("USE_STATIC") ? 1 : 0
    })
})

// All values is "string value"
// Value is boolean TRUE if:
// - not empty("", "    ")
// - and not "FALSE" or "OFF" or "0"
// - in any other case is TRUE

// Predefined global variables
// $NDE_WINDOWS
// $NDE_LINUX
// $NDE_MACOS
// $NDE_UNIX
// $NDE_CC
// $NDE_CXX
// $NDE_PKG_VERSION
// $NDE_PKG_VERSION_MAJOR
// $NDE_PKG_VERSION_MINOR
// $NDE_PKG_VERSION_PATCH
// $NDE_BUILD_DIRECTORY
// $NDE_ROOT_DIRECTORY
// $NDE_HOST_PLATFORM_ARCH
// $NDE_HOST_PLATFORM_NAME
// $NDE_TARGET_PLATFORM_ARCH
// $NDE_TARGET_PLATFORM_NAME
// $NDE_IS_CROSS_COMPILING = ($NDE_HOST_PLATFORM_ARCH != $NDE_TARGET_PLATFORM_ARCH)

make.ensure(function (ok) {
    if (NDE_WINDOWS)
        has.tool("nmake", "~15.2.0")

    if (NDE_UNIX)
        has.tool("make", "~4.0.0")

    has.tool(NDE_CC)
    has.header("curl/easy.h")

    if (option("USE_STATIC"))
        has.lib(env("zlib.LIB_NAME_STATIC"))
    else
        has.lib(env("zlib.LIB_NAME_DYNAMIC"))

    ok();
})

make(function () {
    if (0 > ["1", "2", "3", "4", "5"].indexOf(NDE_PKG_VERSION_MAJOR)) return;

    // support variables
    var FILE_PREFIX = "curl_" + NDE_PKG_VERSION,
        FILE_NAME = FILE_PREFIX + ".zip",
        FILE_PATH = path.combine(NDE_BUILD_DIRECTORY, FILE_NAME),
        DIRECTORY_PATH = path.combine(NDE_BUILD_DIRECTORY, FILE_PREFIX),
        URL = "..."

    // # make actions
    files.download(URL, FILE_PATH)
    files.unzip(FILE_PATH, NDE_BUILD_DIRECTORY)

    // 4 and 5 versions
    if (NDE_PKG_VERSION_MAJOR > 3)
        files.copy("...")

    // all versions
    files.copy(DIRECTORY_PATH, "**/*", NDE_ROOT_DIRECTORY)

    // save & export package configuration
    // essas configurações vão para o arquivo de lock como variáveis de ambiente
    // - quando um pacote é instalado(após resolvido dependências) gera um arquivo de lock "NdeLock.txt"
    // - um save, guarda um valor no arquivo prefixado com o nome do pacote

    // isso abaixo irá gerar uma entrada "mypkg.VERSION"
    env.save("VERSION", NDE_PKG_VERSION)

    // isso abaixo irá exportar "mypkg.VERSION" como uma variável de ambiente chamada "MYPKG_VERSION"
    env.export("VERSION")

    // isso abaixo irá exportar "mypkg.VERSION" como uma variável de ambiente chamada "MYPKG_OTHER_VERSION"
    env.export("VERSION", ID.toUpperCase() + "_OTHER_VERSION")
})

make(/*...*/)
