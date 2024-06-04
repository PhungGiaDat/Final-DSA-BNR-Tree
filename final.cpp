#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <utility>
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
bool IsMale(PERSON x) {return x.gender == true ? true : false;} // kiểm tra giới tính//
void BubbleSort(vector<PERSON> &array);
bool CompareAge(const PERSON& a, const PERSON& b);
void getLivingMembers(NODE* pRoot, vector<PERSON> &members);
void PrintLivingMembers(NODE* pRoot);
int AnalyzeGender(NODE* pRoot,int &malecount,int &femalecount);
void OccupationCount(NODE* pRoot,map<string,int> &jobCounts);
void AnalyzeJob(NODE* pRoot);
void DeletePerson(NODE*& pRoot, string name) ;

int main()
{
    NODE* familyTree;
    Init(familyTree);

    // Data Mẫu
    PERSON person1 = { "Frank Doe", true, "Houston", {8, 8, 1945}, {1, 7, 2020}, "Doctor" };
    PERSON person2 = { "Grace Doe", false, "Dallas", {9, 9, 1940}, {10, 8, 2019}, "Teacher" };
    PERSON person3 = { "John Doe", true, "New York", {1, 1, 1950}, {0, 0, 0}, "Engineer" };
    PERSON person4 = { "Jane Doe", false, "Los Angeles", {2, 2, 1955}, {0, 0, 0}, "Teacher" };
    PERSON person5 = { "Alice Doe", false, "Chicago", {3, 3, 1980}, {0, 0, 0}, "Doctor" };
    PERSON person6 = { "Bob Doe", true, "San Francisco", {4, 4, 1985}, {0, 0, 0}, "Lawyer" };
    PERSON person7 = { "Charlie Doe", true, "Seattle", {5, 5, 2010}, {0, 0, 0}, "Student" };
    PERSON person8 = { "David Doe", true, "Boston", {6, 6, 2015}, {0, 0, 0}, "Student" };
    PERSON person9 = { "Eve Doe", false, "Miami", {7, 7, 2020}, {0, 0, 0}, "Student" };
   

    AddPerson(familyTree, "", person1); // Thêm người gốc
    AddPerson(familyTree, "Frank Doe", person2); // Thêm con
    AddPerson(familyTree, "Frank Doe", person3); // Thêm con khác
    AddPerson(familyTree, "Grace Doe", person4); // Thêm con
    AddPerson(familyTree, "Grace Doe", person5); // Thêm con khác
    AddPerson(familyTree, "Jane Doe", person6); // Thêm con khác
    AddPerson(familyTree, "Jane Doe", person7); // Thêm con khác
    AddPerson(familyTree, "Alice Doe", person8); // Thêm con khác
    AddPerson(familyTree, "Alice Doe", person9); // Thêm con khác



    PrintFamily(familyTree);

    // Tìm một người và in ra thế hệ của họ
    int generation = 1;
    string searchName;
    cout << "Enter the name of the person to find: ";
    cin >> searchName;
    NODE* foundPerson = FindPerson(familyTree, searchName);
    if (foundPerson) {
        cout << "Found person in generation: " << generation << endl;
        PrintPerson(foundPerson->Key);
    }
    else {
        cout << "Khong tim thay" << endl;
    }

    // Tính tổng số tuổi của các thành viên còn sống
    int totalAge = TotalAgeLivingMembers(familyTree);
    cout << "Tong so tuoi cua cac thanh vien con song: " << totalAge << endl;

    // In ra các thành viên chưa có con
    cout << "Cac thanh vien chua co con:" << endl;
    PrintMembersWithoutChildren(familyTree);

    // In ra các thành viên thuộc đời thứ N
    int targetGeneration;
    cout << "Enter the generation number to list members: ";
    cin >> targetGeneration;
    cout << "Cac thanh vien thuoc doi thu " << targetGeneration << ":" << endl;
    PrintMembersOfGeneration(familyTree, targetGeneration, 1);

    // Dem so luong nam va nu trong gia pha
    int malecount; 
    int femalecount;
    AnalyzeGender(familyTree,malecount,femalecount);
    cout << "So luong nam trong gia pha : " << malecount << endl;
    cout << "So luong nu trong gia pha : "<< femalecount << endl;


    // In ra các thành viên còn sống và sắp xếp theo năm sinh
    PrintLivingMembers(familyTree);

    // Thống kê số lượng nghe nghiệp trong gia phả
    AnalyzeJob(familyTree);


    // Xoá bỏ 1 thành viên khỏi cây gia phả
    string deletePersonName;
    cout << "Enter the name of the person to delete: ";
    cin >> deletePersonName;
    DeletePerson(familyTree, deletePersonName);

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
NODE* SearchParent (NODE* pRoot, string name)
{
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
    cout<<x.name<<" ";
    cout<<x.gender<<" ";
    cout<<x.birthPlace<<" ";
    cout<<2024-x.dob.year<<" ";
    x.dod.year == 0  ? cout<<"Còn Sống " : cout<<"Đã mất "; // nếu năm chết = NULL thì còn sống còn không thì đã mất//
    cout<<x.job<<endl;
    cout<<endl;
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

// hàm so sánh năm sinh,tháng,ngày và xác định còn sống hay đã chết
bool CompareAge(const PERSON& a, const PERSON& b) // khai báo hằng số nhằm đảm bảo dữ liệu không thay đổi khi chạy vòng lặp Bubble Sort
{
    if (!a.dod.year && !b.dod.year) // Nếu cả 2 còn sống
    {
        // nếu năm sinh khác nhau
        if(a.dob.year != b.dob.year) return a.dob.year < b.dob.year;
        // nếu khác tháng
        if(a.dob.month != b.dob.month) return a.dob.month < b.dob.month;
        return a.dob.day < b.dob.day;
    }
    else
    {
        if(!a.dod.year || !b.dod.year) return a.dod.year > b.dod.year;
        return a.dod.year < b.dod.year;
    }
}

// hàm sắp xếp BubbleSort
void BubbleSort(vector<PERSON> &array)
{
    int size = array.size();
    for (int i = 0 ; i < size - 1 ; i++ )  
    {
        for (int j = 0 ; j < size - i - 1 ; j++)
        {
            if (CompareAge(array[j],array[j+1]))
            {
                PERSON temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        
        }
    }
}

// hàm lấy ra các thành viên còn sống và cho vào mảng động
void getLivingMembers(NODE* pRoot, vector<PERSON> &members)
{
    if (pRoot == NULL) return;
    // push_back là hàm thêm vào cuối mảng
    // hay là phương thức thêm vào mảng động vì mảng động không cố định kích thước nên phải thêm vào cuối mảng 
    if (pRoot->Key.dod.year == 0) members.push_back(pRoot->Key); 

    getLivingMembers(pRoot->pLeft, members);
    getLivingMembers(pRoot->pRight, members);
}

// câu 7 In ra các thành viên và sắp xếp theo năm,tháng ,ngày sinh
void PrintLivingMembers(NODE* pRoot)
{
    vector<PERSON> livingMembers; // khai báo một mảng động vector với kiểu dữ liệu PERSON
    getLivingMembers(pRoot, livingMembers);
    BubbleSort(livingMembers);
    cout << "Danh sách các thành viên còn sống và sắp xếp theo năm sinh:" << endl;
    // vòng lặp for each  : cho mỗi phần tử member kiểu dữ liệu PERSON trong mảng livingMembers
    // tương tự khai báo hằng số const nhằm đảm bảo dữ liệu không thay đổi
    for (const PERSON& member : livingMembers)  
    {
        PrintPerson(member);
    }
}



// Câu 8: Thống kê nam nữ trong gia phả
int AnalyzeGender(NODE* pRoot,int &malecount,int &femalecount)
{
    if(pRoot == NULL) return 0;


    if (pRoot->pLeft == NULL && pRoot->pRight == NULL)
    {
        if (IsMale(pRoot->Key)) return malecount = 1; 
        else return femalecount = 1;
    }

    else
    {
        if (IsMale(pRoot->Key))
        {
            return malecount = AnalyzeGender(pRoot->pLeft,malecount,femalecount) + AnalyzeGender(pRoot->pRight,malecount,femalecount);
        }
        else 
        {
            return femalecount = AnalyzeGender(pRoot->pLeft,malecount,femalecount) + AnalyzeGender(pRoot->pRight,malecount,femalecount);
        }
    }
}


// Hàm sử dụng map để lấy ra một dictionary các phần tử trùng lặp với key là job và value là số lần trùng lặp
void OccupationCount(NODE* pRoot,map<string,int> &jobCounts)
{
    if(pRoot == NULL) return;

    // nếu chỉ có gốc thì trả về 1
    if (pRoot->pLeft == NULL && pRoot->pRight == NULL)
    {
        jobCounts[pRoot->Key.job]++;
    }

    // ngược lại tăng dần số lần trùng lặp
    else
    {
        jobCounts[pRoot->Key.job]++;
        OccupationCount(pRoot->pLeft,jobCounts);
        OccupationCount(pRoot->pRight,jobCounts);
    }
}

// Câu 9 In ra nghề có thành viên cao nhất
void AnalyzeJob(NODE* pRoot)
{
    map<string,int> maxJob;
    OccupationCount(pRoot,maxJob);

    // Khai báo một biến để chứa nghề có số lượng lớn nhất
    pair<string,int> HighestJob; 

    cout << "Thong ke so luong nghe nghiep trong gia pha:" << endl;
    // Duyệt vòng lặp Với mỗi biến job trong dictionary maxJob
    // khai báo một biến job kiểu dữ liệu pair<string,int> trong maxJob
    // pair là một cặp giá trị key và value trong dictionary NHƯNG CHỈ LÀ 1 BIẾN ĐƠN
    for (const pair<string,int>& job : maxJob)
    {
        cout << job.first << ": " << job.second << endl;
        // hàm kiểm tra nghề có số lượng lớn nhất
        // second tương tự cho value trong dictionary
        if (job.second > HighestJob.second)
        {
            HighestJob = job;
        }
    }
    cout << "Nghe co so luong thanh vien nhieu nhat: " << HighestJob.first << ":" << HighestJob.second << endl;
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

