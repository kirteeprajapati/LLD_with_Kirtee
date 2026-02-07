#include <string>
#include <stdexcept>
#include <vector>
#include <unordered_map> 

class Directory; // Forward declaration // to break the cycle of child-parent-child calling each other
// also this tell the compiler "Trust me it exist"

class Node{
protected:                          // so that child can use/modify them without getters
    std::string name;              // name we can copy it not that expensive
    Directory * parent;           // every file/Directory should know their parent
    // Forward Declared Directory so that Node do not screem that it do not exist
    
public:
    // here we'll have construtor, distroyer, getters and setters
    Node(const std::string &name, Directory* parent) : name(std::move(name)), parent(parent) {}
    
    virtual ~Node()=default;    // letting compiler use default behaviour to delete Node
    
    std::string getName() const{
        return name;
    }
    
    Directory *getParent() const{
        return parent;
    }
    
    virtual bool isFile() const=0;      // virtually declared here to make sure who so ever extends this Class should have these methods for sure.
    virtual size_t getSize() const=0;
};

class File : public Node{           // extends Node publically
protected:
    std::string content;
    
public:
    // Constructor
    File(const std::string &name, Directory *parent) : Node(name, parent) {}

    // getters
    bool isFile() const override{
        return true;
    }
    
    // Setters
    void write(const std::string &data){     // passing by reference to avoid expensive copy operation
        content += data;
    }
    
    std::string read() const{
        return content;
    }
    
    size_t getSize() const override{
        return content.size();
    }
};

class Directory : public Node{
    private:
        std::unordered_map<std::string, std::unique_ptr<Node>> children;
    // File/Folder name mapped to the node for O(1) lookup stores what inside sirectory immediate
    // Directory Ows the child so unique pointer 
    public:
        Directory(const std::string &name, Directory* parent=nullptr) 
            : Node(name, parent){}
    
    bool isFile() const override{
        return false;
    }
    
    size_t getSize() const override{
        size_t total = 0;
        for(const auto&[_,child] : children){
            total+=child->getSize();
        }
        return total;
    }
    
    bool exists(const std::string &name) const{
        return children.find(name)!=children.end();
    }
    
    Node* get(const std::string &name) const{
        auto it = children.find(name);
        return it ==children.end() ? nullptr : it->second.get();  
        // recursive
    }
    
    void add(std::unique_ptr<Node> node){
        children[node->getName()] = std::move(node);
    }
    
    void remove(const std::string& name){
        children.erase(name);
    }
    
    std::vector<std::string> list() const{
        std::vector<std::string> result;
        for(const auto&[name, _]: children){
            result.push_back(name);
        }
        return result;
    }
    
};

// Facade : Path traversal lives here

class FileSystem{
private:
    std::unique_ptr<Directory> root;
    
    std::vector<std::string> split(const std::string&path){ 
        // "/user/bin/text.txt"
        std::stringstream ss(path);
        std::string token;
        std::vector<std::string> parts;
        
        while(std::getline(ss, token, '/')){
            if(!token.empty()){
                parts.push_back(token);
            }
        }
        return parts; // as vector of string
    }
    
    Directory* traverseToParent(const std::vector<std::string> &parts){
        Directory* curr = root.get();
        for(size_t i=0; i+1<parts.size(); i++){
            Node* next = curr->get(parts[i]);
            if(!next || next->isFile()){
                throw std::runtime_error("Invalid Path");
            }
            curr = static_cast<Directory*>(next);
        }
        return curr;
    }
    
public:
    FileSystem(){
        root=std::make_unique<Directory>("/");
    }
    
    void mkdir(const std::string &path){
        auto parts = split(path);
        Directory* parent = traverseToParent(parts);
        
        const std::string& dirName = parts.back();
        if(parent->exists(dirName)){
            throw std::runtime_error("Directory already exists");
        }
        
        parent->add(std::make_unique<Directory>(dirName, parent));
    }
    
    void createFile(const std::string& path){
        auto parts = split(path);
        Directory* parent = traverseToParent(parts);
        
        const std::string& fileName = parts.back();
        if(parent->exists(fileName)){
            throw std::runtime_error("File already exists");
        }
        
        parent->add(std::make_unique<File>(fileName, parent));
    }
    
    void writeFile(const std::string &path, const std::string &data){
        auto parts = split(path);
        Directory* parent = traverseToParent(parts);
        
        Node* node = parent->get(parts.back());
        if(!node||!node->isFile()){
            throw std::runtime_error("File not found");
        }
        static_cast<File*> (node)->write(data);
    }
    
    std::string readFile(const std::string& path){
        auto parts = split(path);
        Directory* parent = traverseToParent(parts);
        
        Node* node = parent->get(parts.back());
        if(!node || !node->isFile()){
            throw std::runtime_error("File not found");
        }
        return static_cast<File* > (node)->read();
    }
    
    std::vector<std::string> listDir(const std::string&path){
        auto parts = split(path);
        Directory* curr = root.get();
        
        for(const auto&p : parts){
            Node* next = curr->get(p);
            if(!next || next->isFile()){
                throw std::runtime_error("Invalid Directory");
            }
            curr = static_cast<Directory*> (next);
        }
        return curr->list();
    }
};

int main(){
    FileSystem fs;
    fs.mkdir("/usr");
    fs.mkdir("/usr/bin");
    fs.createFile("/usr/bin/app");
    fs.writeFile("/usr/bin/app", "Hello World");
    std::cout<<fs.readFile("/usr/bin/app");
}
