#include <bits/stdc++.h>
using namespace std;

/*
====================================
 In-Memory File System (LLD Ready)
 Composite Design Pattern
====================================
*/

// We support: mkdir /a/b, addFile /a/b/file.txt, ls /a/b, readFile, delete, Path-based traversal

// ----------- Base Component -----------
class FileSystemNode {
protected:
    string name;

public:
    explicit FileSystemNode(string name) : name(move(name)) {}
    virtual ~FileSystemNode() = default;

    string getName() const {
        return name;
    }

    virtual bool isDirectory() const = 0;
};

// ----------- File -----------
class File : public FileSystemNode {
    string content;

public:
    File(string name, string content = "")
        : FileSystemNode(move(name)), content(move(content)) {}

    bool isDirectory() const override {
        return false;
    }

    string read() const {
        return content;
    }

    void write(const string& data) {
        content = data;
    }
};

// ----------- Directory (Composite) -----------
class Directory : public FileSystemNode {
    unordered_map<string, shared_ptr<FileSystemNode>> children;

public:
    explicit Directory(string name)
        : FileSystemNode(move(name)) {}

    bool isDirectory() const override {
        return true;
    }

    bool exists(const string& name) const {
        return children.count(name);
    }

    void add(shared_ptr<FileSystemNode> node) {
        children[node->getName()] = node;
    }

    void remove(const string& name) {
        children.erase(name);
    }

    shared_ptr<FileSystemNode> get(const string& name) const {
        if (!exists(name)) return nullptr;
        return children.at(name);
    }

    vector<string> list() const {
        vector<string> result;
        for (const auto& [name, _] : children) {
            result.push_back(name);
        }
        sort(result.begin(), result.end());
        return result;
    }
};

// ----------- File System Facade -----------
class FileSystem {
    shared_ptr<Directory> root;

    vector<string> split(const string& path) {
        vector<string> tokens;
        string token;
        stringstream ss(path);
        while (getline(ss, token, '/')) {
            if (!token.empty()) tokens.push_back(token);
        }
        return tokens;
    }

    shared_ptr<Directory> traverseToParent(const string& path) {
        auto tokens = split(path);
        shared_ptr<Directory> curr = root;

        for (int i = 0; i < (int)tokens.size() - 1; i++) {
            auto node = curr->get(tokens[i]);
            if (!node || !node->isDirectory()) {
                return nullptr;
            }
            curr = static_pointer_cast<Directory>(node);
        }
        return curr;
    }

public:
    FileSystem() {
        root = make_shared<Directory>("/");
    }

    void mkdir(const string& path) {
        auto tokens = split(path);
        shared_ptr<Directory> curr = root;

        for (const auto& dir : tokens) {
            if (!curr->exists(dir)) {
                curr->add(make_shared<Directory>(dir));
            }
            curr = static_pointer_cast<Directory>(curr->get(dir));
        }
    }

    void addFile(const string& path, const string& content = "") {
        auto parent = traverseToParent(path);
        if (!parent) return;

        auto tokens = split(path);
        string fileName = tokens.back();

        parent->add(make_shared<File>(fileName, content));
    }

    vector<string> ls(const string& path) {
        if (path == "/") return root->list();

        auto tokens = split(path);
        shared_ptr<FileSystemNode> curr = root;

        for (const auto& token : tokens) {
            auto dir = static_pointer_cast<Directory>(curr);
            curr = dir->get(token);
            if (!curr) return {};
        }

        if (curr->isDirectory()) {
            return static_pointer_cast<Directory>(curr)->list();
        }

        return {curr->getName()};
    }

    string readFile(const string& path) {
        auto parent = traverseToParent(path);
        if (!parent) return "";

        auto tokens = split(path);
        auto node = parent->get(tokens.back());

        if (!node || node->isDirectory()) return "";
        return static_pointer_cast<File>(node)->read();
    }

    void deletePath(const string& path) {
        auto parent = traverseToParent(path);
        if (!parent) return;

        auto tokens = split(path);
        parent->remove(tokens.back());
    }
};

// ----------- Demo / Test -----------
int main() {
    FileSystem fs;

    fs.mkdir("/a/b");
    fs.addFile("/a/b/file.txt", "Hello LLD Interview");

    for (auto& name : fs.ls("/a/b")) {
        cout << name << " ";
    }
    cout << endl;

    cout << fs.readFile("/a/b/file.txt") << endl;

    fs.deletePath("/a/b/file.txt");

    return 0;
}
