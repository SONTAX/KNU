#ifndef PERFECTHASH_FILESYSTEM_H
#define PERFECTHASH_FILESYSTEM_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Folder{
    int id;
    string folder_name;
    vector<int> files_id;
    static int next_id;
public:
    Folder();
    Folder(const string& _folder_name);
    Folder(const string& _folder_name, const vector<int>& _files_id);
    string GetFolderName();
    void SetFolderName(string name);
    static vector<Folder> FoldersGenerator(int count);
};

class File {
    string file_name;
    string file_type;
    int id;
    int file_size;
    static int next_id;
public:
    File();
    File(const string& _file_name, const string& _file_type, int _file_size);
};

#endif //PERFECTHASH_FILESYSTEM_H