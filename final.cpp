#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct DATE{
    int day;
    int month;
    int year;
};

struct PERSON{
    string name;
    bool gender;
    string birthPlace;
    DATE dob;
    DATE dod;
    string job;
};

struct NODE{
    PERSON Key;
    NODE* pLeft;
    NODE* pRight;
};


NODE* CreateNode(PERSON x);
void Init(NODE* &pRoot);
void InputPersonInfo(PERSON &x);
NODE* SearchParent(NODE* pRoot, string name); 
int AddPerson(NODE* &pRoot, string parentName, PERSON x);
void PrintFamily(NODE* pRoot);
void PrintPerson(PERSON x);
NODE* FindPerson(NODE* pRoot, string name);
int TotalAgeLivingMembers(NODE* pRoot);
void PrintMembersWithoutChildren(NODE* pRoot);
void PrintMembersOfGeneration(NODE* pRoot, int targetGeneration, int currentGeneration); 
void DeletePerson(NODE*& pRoot, string name) ;

int main()
{
    NODE* FamilyTree;
    Init(FamilyTree);
    //nhap thong tin 1 nguoi
    PERSON x;
    InputPersonInfo(x);
    if(AddPerson(FamilyTree,"",x)) cout<<"Them thanh cong";
    else cout<<"Them khong thanh cong";

    //nhap thong tin 1 nguoi
    InputPersonInfo(x);
    if(AddPerson(FamilyTree,"Nam",x)) cout<<"Them thanh cong";
    else cout<<"Them khong thanh cong";

    InputPersonInfo(x);
    if(AddPerson(FamilyTree,"Thắng",x)) cout<<"Them thanh cong";
    else cout<<"Them khong thanh cong";

    InputPersonInfo(x);
    if(AddPerson(FamilyTree,"Thắng",x)) cout<<"Them thanh cong";
    else cout<<"Them khong thanh cong";

    InputPersonInfo(x);
    if(AddPerson(FamilyTree,"Thái",x)) cout<<"Them thanh cong";
    else cout<<"Them khong thanh cong";

     InputPersonInfo(x);
    if(AddPerson(FamilyTree,"",x)) cout<<"Them thanh cong";
    else cout<<"Them khong thanh cong";


    PrintFamily(FamilyTree);
    return 0;
}

NODE* CreateNode(PERSON x){
    NODE* pNode = new NODE;
    pNode->Key = x;
    pNode->pLeft = pNode->pRight = NULL;
    return pNode;
}

void Init(NODE* &pRoot){
    pRoot = NULL;
}


void InputPersonInfo(PERSON &x)
{
    cin>>x.name;
    cin>>x.gender;
    cin>>x.birthPlace;
    cin>>x.dob.day>>x.dob.month>>x.dob.year;
    cin>>x.dod.day>>x.dod.month>>x.dod.year;
    cin>>x.job;
}

// hàm tìm tên cha của một người hoặc node cha của 1 node//
NODE* SearchParent (NODE* pRoot, string name){
    if(pRoot == NULL) return NULL;
    if(pRoot->Key.name == name) // NẾU TÌM THẤY TÊN NODE CHA
    {
        cout<<pRoot->Key.name;
        return pRoot; //TRẢ VỀ NODE CHA
    }
    NODE* pNode = NULL; // khởi tạo con trỏ node để chạy//
    if (pNode == NULL) pNode = SearchParent(pRoot->pLeft, name); //đi sang trái//
    if (pNode == NULL) pNode = SearchParent(pRoot->pRight, name); // đi sang phải//
    // bằng cách đệ quy hàm sẽ đi lần lượt từ trên xuống trái sang phải //
    // mỗi lần gọi lại chính nó sẽ kiểm tra xem pRoot có NULL không//
    // pRoot chính là con trỏ hay lính canh đi từ gốc//
    
    return pNode; // trả về node cha//
}

int AddPerson(NODE* &pRoot,string parentname,PERSON person)
{
    if(pRoot == NULL)
    {
        pRoot = CreateNode(person);
        return 1;
    }
    NODE* parent = SearchParent(pRoot,parentname); // khởi tạo một node cha//
    if(parent == NULL) return 0; // nếu không tìm thấy node cha thì trả về 0//
    
    // nếu cây bên trái trống thì ưu tiên thêm vào bên trái//
    if (parent->pLeft == NULL)
    {
        parent->pLeft = CreateNode(person);
        return 1;
    }
    // nếu cây nhánh bên trái có thì bên phải trống thêm vào bên phải//
    if (parent->pRight == NULL)
    {
        parent->pRight = CreateNode(person);
        return 1;
    }
    return 0;
}

void PrintPerson(PERSON x)
{
    cout<<x.name<<endl;
    cout<<x.gender<<endl;
    cout<<x.birthPlace<<endl;
    cout<<2024-x.dob.year<<endl;
    x.dod.year == 0  ? cout<<"Còn Sống" : cout<<"Đã mất"; // nếu năm chết = NULL thì còn sống còn không thì đã mất//
    cout<<x.job<<endl;
}

void PrintFamily(NODE* pRoot)
{
    if(pRoot != NULL) // điều kiện cũng như điểm dừng cho đệ quy // nếu pRoot = NULL thì dừng lại
    {
        PrintPerson(pRoot->Key); // vì pRoot key là dữ liệu PERSON nên không cần khai báo 1 biến khác
        PrintFamily(pRoot->pLeft); // đi sang trái 
        PrintFamily(pRoot->pRight); // tương tự đi sang phải nhờ đệ quy
    }
    // đệ quy sẽ dừng khi pRoot = NULL
}


NODE* FindPerson(NODE* pRoot,string name)
{
    if(pRoot == NULL) return NULL;
    if(pRoot->Key.name == name) return pRoot;  else cout<<"Khong Tim thay";// tìm thấy //
    NODE* pNode = NULL; // khởi tạo con trỏ node để chạy//
    if(pNode == NULL) pNode = FindPerson(pRoot->pLeft, name);
    if(pNode == NULL) pNode = FindPerson(pRoot->pRight, name);
    return pNode;
}

// Câu 4: Tính tổng số tuổi của các thành viên còn sống trong gia phả
int TotalAgeLivingMembers(NODE* pRoot) 
{
    if (pRoot == NULL) return 0;

    int age = 0;
    if (pRoot->Key.dod.year == 0) {
        age = 2024 - pRoot->Key.dob.year;
    }
    
    return age += TotalAgeLivingMembers(pRoot->pLeft) + TotalAgeLivingMembers(pRoot->pRight);
}

// Câu 5: Duyệt cây gia phả để in ra các thành viên chưa có con
void PrintMembersWithoutChildren(NODE* pRoot) 
{
    if (pRoot == NULL) return;

    if (pRoot->pLeft == NULL && pRoot->pRight == NULL) {
        PrintPerson(pRoot->Key);
    }
    PrintMembersWithoutChildren(pRoot->pLeft);
    PrintMembersWithoutChildren(pRoot->pRight);
}

// Câu 6: Duyệt cây và in ra tất cả thành viên thuộc đời thứ N
void PrintMembersOfGeneration(NODE* pRoot, int targetGeneration, int currentGeneration) 
{
    if (pRoot == NULL) return;
    if (currentGeneration == targetGeneration) {
        PrintPerson(pRoot->Key);
    }
    PrintMembersOfGeneration(pRoot->pLeft, targetGeneration, currentGeneration + 1);
    PrintMembersOfGeneration(pRoot->pRight, targetGeneration, currentGeneration + 1);
}


// Câu 10:  Xóa bỏ 1 thành viên khỏi cây gia phả

void DeletePerson(NODE*& pRoot, string name) 
{
    if (pRoot == NULL) return;

    if (pRoot->Key.name == name) {
        // Trường hợp nút không có con
        if (pRoot->pLeft == NULL && pRoot->pRight == NULL) {
            delete pRoot;
            pRoot = NULL;
        }
        // Trường hợp nút chỉ có nhánh trái
        else if (pRoot->pRight == NULL) {
            NODE* temp = pRoot;
            pRoot = pRoot->pLeft;
            delete temp;
        }
        // Trường hợp nút chỉ có nhánh phải
        else if (pRoot->pLeft == NULL) {
            NODE* temp = pRoot;
            pRoot = pRoot->pRight;
            delete temp;
        }
        // Trường hợp nút có cả hai nhánh
        else {
            NODE* temp = pRoot->pRight;
            while (temp->pLeft != NULL) {
                temp = temp->pLeft;
            }
            pRoot->Key = temp->Key;
            DeletePerson(pRoot->pRight, temp->Key.name);
        }
    }
    else {
        DeletePerson(pRoot->pLeft, name);
        DeletePerson(pRoot->pRight, name);
    }
}