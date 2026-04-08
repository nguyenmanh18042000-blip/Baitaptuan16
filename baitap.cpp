#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>

using namespace std;

// 1. Khai bao cau truc file (Node)
struct FileNode {
    string fileName;
    double fileSize; // Don vi: GB
    time_t createdAt;
    FileNode* next;
};

// Ham tao node moi
FileNode* createFile(string name, double size, time_t timeCreated) {
    FileNode* newNode = new FileNode();
    newNode->fileName = name;
    newNode->fileSize = size;
    newNode->createdAt = timeCreated;
    newNode->next = NULL;
    return newNode;
}// 2. Ham chen file theo thu tu thoi gian
void insertSorted(FileNode* &head, string name, double size, time_t timeCreated) {
    FileNode* newNode = createFile(name, size, timeCreated);
    if (head == NULL || head->createdAt >= newNode->createdAt) {
        newNode->next = head;
        head = newNode;
    } else {
        FileNode* current = head;
        while (current->next != NULL && current->next->createdAt < newNode->createdAt) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// 3. Tinh tong kich thuoc file
double getTotalSize(FileNode* head) {
    double total = 0;
    while (head != NULL) {
        total += head->fileSize;
        head = head->next;
    }
    return total;
}

// 4. Loai bo file nho nhat de vua USB 32GB
void backupToUSB(FileNode* &head) {
    while (getTotalSize(head) > 32.0 && head != NULL) {
        FileNode *minNode = head, *curr = head, *minPrev = NULL, *tempPrev = NULL;
        while (curr != NULL) {
            if (curr->fileSize < minNode->fileSize) {
                minNode = curr;
                minPrev = tempPrev;
            }
            tempPrev = curr;
            curr = curr->next;
        }
        if (minNode == head) head = head->next;
        else if (minPrev != NULL) minPrev->next = minNode->next;
        delete minNode;
    }
}

int main() {
    FileNode* myFiles = NULL;
    insertSorted(myFiles, "Video_BongDa.mp4", 15.0, 1712580000);
    insertSorted(myFiles, "DoAn_Electronics.pdf", 20.0, 1712585000); 
    
    std::cout << "Tong dung luong truoc backup: " << getTotalSize(myFiles) << " GB" << std::endl;
    backupToUSB(myFiles);
    std::cout << "Tong dung luong sau khi vua USB 32GB: " << getTotalSize(myFiles) << " GB" << std::endl;
    
    return 0;
}