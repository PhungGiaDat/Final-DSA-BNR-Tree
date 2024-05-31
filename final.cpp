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
int main()
{
    return 0;
}

NODE* CreateNode(PERSON x){
    NODE* pNode = new NODE;
    pNode->Key = x;
    pNode->pLeft = pNode->pRight = NULL;
}

void Init(NODE* &pRoot){
    pRoot = NULL;
}


void Input(PERSON &x)
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
    if(pRoot == NULL) return;
    if(pRoot->Key.name == name) // NẾU TÌM THẤY TÊN NODE CHA
    {
        cout<<pRoot->Key.name;
        return pRoot; //TRẢ VỀ NODE CHA
    }
    SearchParent(pRoot->pLeft, name); //đi sang trái//
    SearchParent(pRoot->pRight, name); // đi sang phải//
    // bằng cách đệ quy hàm sẽ đi lần lượt từ trên xuống trái sang phải //
    // mỗi lần gọi lại chính nó sẽ kiểm tra xem pRoot có NULL không//
    // pRoot chính là con trỏ hay lính canh đi từ gốc//
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
    
}

void PrintPerson(PERSON x)
{
    cout<<x.name<<endl;
    cout<<x.gender<<endl;
    cout<<x.birthPlace<<endl;
    cout<<2024-x.dob.year<<endl;
    x.dod.year == NULL ? cout<<"Còn Sống" : cout<<"Đã mất";
    cout<<x.job<<endl;
}

void printFamily(NODE* pRoot)
{
    if(pRoot != NULL) // điều kiện cũng như điểm dừng cho đệ quy // nếu pRoot = NULL thì dừng lại
    {
        PrintPerson(pRoot->Key); // vì pRoot key là dữ liệu PERSON nên không cần khai báo 1 biến khác
        printFamily(pRoot->pLeft); // đi sang trái 
        printFamily(pRoot->pRight); // tương tự đi sang phải nhờ đệ quy
    }
    // đệ quy sẽ dừng khi pRoot = NULL
}
