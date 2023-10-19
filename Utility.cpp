#include "Utility.h"
#include	<filesystem>
#include "Debug.h"
namespace fs = std::filesystem;

std::string GetFileName(std::string FilePath)
{
    // u8エンコードでｐａｔｈをコンストラクト
    fs::path p = fs::u8path(FilePath.c_str());
    // パスから、ファイル名を除いたディレクトリ、ファイル名、
    // 拡張子を除いたファイル名、拡張子を抽出
//    DEBUG_LOG("ディレクトリ名 : " << p.parent_path());
//    DEBUG_LOG("ファイル名  : " << p.filename());
//    DEBUG_LOG("ファイル名（拡張子なし） : " << p.stem());
//    DEBUG_LOG("拡張子 : " << p.extension());

    return p.filename().string();
}

// ファイルパスからファイル名だけを取得する
std::wstring GetFileNameWide(std::string filepath) {

    // u8エンコードでｐａｔｈをコンストラクト
//    fs::path p = fs::u8path(filepath.c_str());
    fs::path p = fs::path(filepath.c_str());

    // システムＷＩＤＥ文字で取得
    const std::wstring wsfilename = p.filename().wstring();

    // ロケールを日本にする
    setlocale(LC_ALL, "Japanese");
    WDEBUG_LOG(wsfilename);

    return wsfilename;
}

// ファイルパスからファイル拡張子を取得する
std::string GetFileExt(std::string filepath) {

    // UTF-8
//    fs::path p = fs::u8path(filepath.c_str());
    fs::path p = fs::path(filepath.c_str());

    return p.extension().string();
}

// ファイルパス(UTF16)からファイル拡張子を取得する
std::wstring GetFileExtWide(std::string filepath) {

    //u8エンコードでｐａｔｈをコンストラクト
    fs::path p = fs::u8path(filepath.c_str());

    return p.extension().wstring();
}

// ファイルパスから親ディレクトリを取得する
std::wstring GetParentDirectoryWide(std::string filepath) {

    // u8エンコードでｐａｔｈをコンストラクト
    fs::path p = fs::u8path(filepath.c_str());

    // システムＷＩＤＥ文字(UTF-16)で取得
    std::wstring wsparentdirectory;

    // 親ディレクトリを持っているか？
    if (p.has_parent_path()) {
        wsparentdirectory = p.parent_path().wstring() + L"\\";
    }
    else {
        wsparentdirectory = L"\\";
    }

    return wsparentdirectory;
}