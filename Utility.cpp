#include "Utility.h"
#include	<filesystem>
#include "Debug.h"
namespace fs = std::filesystem;

std::string GetFileName(std::string FilePath)
{
    // u8�G���R�[�h�ł����������R���X�g���N�g
    fs::path p = fs::u8path(FilePath.c_str());
    // �p�X����A�t�@�C�������������f�B���N�g���A�t�@�C�����A
    // �g���q���������t�@�C�����A�g���q�𒊏o
//    DEBUG_LOG("�f�B���N�g���� : " << p.parent_path());
//    DEBUG_LOG("�t�@�C����  : " << p.filename());
//    DEBUG_LOG("�t�@�C�����i�g���q�Ȃ��j : " << p.stem());
//    DEBUG_LOG("�g���q : " << p.extension());

    return p.filename().string();
}

// �t�@�C���p�X����t�@�C�����������擾����
std::wstring GetFileNameWide(std::string filepath) {

    // u8�G���R�[�h�ł����������R���X�g���N�g
//    fs::path p = fs::u8path(filepath.c_str());
    fs::path p = fs::path(filepath.c_str());

    // �V�X�e���v�h�c�d�����Ŏ擾
    const std::wstring wsfilename = p.filename().wstring();

    // ���P�[������{�ɂ���
    setlocale(LC_ALL, "Japanese");
    WDEBUG_LOG(wsfilename);

    return wsfilename;
}

// �t�@�C���p�X����t�@�C���g���q���擾����
std::string GetFileExt(std::string filepath) {

    // UTF-8
//    fs::path p = fs::u8path(filepath.c_str());
    fs::path p = fs::path(filepath.c_str());

    return p.extension().string();
}

// �t�@�C���p�X(UTF16)����t�@�C���g���q���擾����
std::wstring GetFileExtWide(std::string filepath) {

    //u8�G���R�[�h�ł����������R���X�g���N�g
    fs::path p = fs::u8path(filepath.c_str());

    return p.extension().wstring();
}

// �t�@�C���p�X����e�f�B���N�g�����擾����
std::wstring GetParentDirectoryWide(std::string filepath) {

    // u8�G���R�[�h�ł����������R���X�g���N�g
    fs::path p = fs::u8path(filepath.c_str());

    // �V�X�e���v�h�c�d����(UTF-16)�Ŏ擾
    std::wstring wsparentdirectory;

    // �e�f�B���N�g���������Ă��邩�H
    if (p.has_parent_path()) {
        wsparentdirectory = p.parent_path().wstring() + L"\\";
    }
    else {
        wsparentdirectory = L"\\";
    }

    return wsparentdirectory;
}