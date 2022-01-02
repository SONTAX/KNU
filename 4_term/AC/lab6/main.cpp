#include "BPlusTree.h"

int main() {
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
    BPlusTree tree(2);
    for (int i = 0; i < 10; i++){
        std::cout << "-----------------------------------INSERT " << i << " ---------------------------\n";
        tree.insert(i, folders_name[i]);
        tree.print();
    }
    return 0;
}