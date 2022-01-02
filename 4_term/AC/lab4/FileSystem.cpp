#include "FileSystem.h"

int Folder::next_id = 0;
int File::next_id = 0;

string folders_name [] = {
        "System",
        "Boot",
        "Branding",
        "CSC",
        "Debug",
        "Cursor",
        "AppPatch",
        "AppReadiness",
        "Media",
        "Download",
        "OCR",
        "Panther",
        "PLA",
        "Print",
        "Cache",
        "Setup",
        "Service",
        "Tasks",
        "TAPI",
        "Web"
};

Folder::Folder() {
    id = next_id++;
    folder_name = "";
    files_id.clear();
}

Folder::Folder(const string &_folder_name) {
    id = next_id++;
    folder_name = _folder_name;
    files_id.clear();
}

Folder::Folder(const string& _folder_name, const vector<int>& _files_id) {
    id = next_id++;
    folder_name = _folder_name;
    for(auto s : _files_id){
        files_id.push_back(s);
    }
}

string Folder::GetFolderName() {
    return folder_name;
}

void Folder::SetFolderName(string name) {
    folder_name = name;
}

vector<Folder> Folder::FoldersGenerator(int count) {
    int id;
    string name;
    vector<Folder> res;
    for(size_t i = 0; i < count; i++){
        name = folders_name[i];
        Folder folder_to_add(name);
        res.push_back(folder_to_add);
    }
    return res;
}

File::File() {
    id = next_id++;
    file_name = "";
    file_type = "";
    file_size = -1;
}

File::File(const string &_file_name, const string &_file_type, int _file_size) {
    id = next_id++;
    file_name = _file_name;
    file_type = _file_type;
    file_size = _file_size;
}