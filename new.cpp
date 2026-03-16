// 11327102 林姿妤
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

struct Data {
  int num; // 學校代碼										
  std::string school_name; // 學校名稱
  int department_num; // 科系代碼
  std::string department_name; // 科系名稱
  std::string Daytime; // 日間∕進修別
  std::string level; // 等級別
  int student_num; // 學生數
  int teacher_num; // 教師數
  int graduate_num; // 上學年度畢業生數
  std::string city_name; // 縣市名稱
  std::string system_type; // 體系別
};


struct HeapData {
  int num = 0; 										
  int graduate_num; // 上學年度畢業生數
};

class MaxHeap {
   public:
    std::vector<HeapData> data;

    bool isEmpty() {
        if ( data.size() == 0) {
            return true;
        }
        return false;
    }

    void built_maxheap (std::vector<Data> d) {
        int num = 1;
        for (int i = 0; i < d.size(); i++) {
            insert_maxheap (d[i], num);
            num++;
        }
        return;
    }

    void insert_maxheap (Data d, int num) {
        HeapData temp;
        temp.graduate_num = d.graduate_num;
        temp.num = num;
        data.push_back(temp);
        int place = data.size() - 1;
        int parent = (place - 1) / 2;
        while ( parent >= 0 && data[place].graduate_num > data[parent].graduate_num ) {
            HeapData temp2 = data[place];
            data[place] = data[parent];
            data[parent] = temp2;
            place = parent;
            parent = (place - 1) / 2;
        } 
        return;
    }
    

    int left_bottom_idx(int n) {

        int level_nodes = 1;  // 每層節點數量
        int total_nodes = 0;  // 已經計算的節點數

        while (total_nodes + level_nodes < n) {
            total_nodes = total_nodes + level_nodes;
            level_nodes = level_nodes * 2;
        }

        return total_nodes;
    }


};

class Deap {
   public:
    std::vector<HeapData> data;

    Deap() {
        HeapData dummy;
        data.push_back(dummy);
    }

    void reset() {
        HeapData dummy;
        data.push_back(dummy);
        return;
    }

    bool isEmpty() {
        if ( data.size() <= 1) {
            return true;
        }
        return false;
    }

    bool is_minheap(int idx, int &level) {
        level = (int)floor(log2(idx + 1));
        int leftofmax = exp2(level - 1) * 3 - 1;
        if ( idx < leftofmax ) {
            return true;
        }
        return false;
    }


    int corresponding_point(bool is_minheep, int level, int idx) {
        if ( idx == 1 ) {
            return idx;
        }
        int displacement = exp2(level - 1);
        if ( is_minheep ) {
            int parent = (idx + displacement - 1) / 2;
            return parent;
        }
        return idx - displacement;
    }

    void built_deap (std::vector<Data> d) {
        int num = 1;
        int place = 1;
        int level = 0;
        for (int i = 0; i < d.size(); i++) {
            HeapData node;
            node.graduate_num = d[i].graduate_num;
            node.num = num; 
            data.push_back(node);
            int place = data.size() - 1;
            bool is_min = is_minheap(place, level);
            if ( is_min ) { // minheap
                int correspond_point = corresponding_point(is_min, level, place);
                if ( data[correspond_point].graduate_num < data[place].graduate_num ) { // maxheap
                    HeapData temp2;
                    temp2 = data[correspond_point];
                    data[correspond_point] = data[place];
                    data[place] = temp2;
                    place = correspond_point;
                    insert_maxheap (place);
                }
                
                else {
                    insert_minheap (place);
                }
            }

            else { // maxheap
                int correspond_point = corresponding_point(is_min, level, place);
                if ( data[correspond_point].graduate_num > data[place].graduate_num ) { // minheap
                    HeapData temp2;
                    temp2 = data[correspond_point];
                    data[correspond_point] = data[place];
                    data[place] = temp2;
                    place = correspond_point;
                    insert_minheap (place);
                }
                
                else {
                    insert_maxheap (place);
                }
            }
            
            num++;
        }
        return;
    }

    void insert_maxheap (int place) {
        int parent = (place - 1) / 2;
        while ( parent >= 2 && data[place].graduate_num > data[parent].graduate_num ) {
            HeapData temp2 = data[place];
            data[place] = data[parent];
            data[parent] = temp2;
            place = parent;
            parent = (place - 1) / 2;
        } 
        return;
    }

    void insert_minheap (int place) {
        int parent = (place - 1) / 2;
        while ( parent >= 1 && data[place].graduate_num < data[parent].graduate_num ) {
            HeapData temp2 = data[place];
            data[place] = data[parent];
            data[parent] = temp2;
            place = parent;
            parent = (place - 1) / 2;
        } 
        return;
    }

    int left_bottom_idx(int n) {

        int level_nodes = 1;  // 每層節點數量
        int total_nodes = 0;  // 已經計算的節點數

        while (total_nodes + level_nodes < n) {
            total_nodes = total_nodes + level_nodes;
            level_nodes = level_nodes * 2;
        }

        return total_nodes;
    }

    void print_test() {
        for (int i = 0; i < data.size(); i++) {
            std::cout << data[i].num << "\t";
            std::cout << data[i].graduate_num << "/";
        }
        std::cout << "\n";
        return;
    }
};

class minmax {
   public:
    std::vector<HeapData> data;

    bool isEmpty() {
        if ( data.size() == 0) {
            return true;
        }
        return false;
    }

    void built_minmax (std::vector<Data> d) {
        int num = 1;
        int place = 1;
        int level = 0;
        for (int i = 0; i < d.size(); i++) {
            HeapData node;
            node.graduate_num = d[i].graduate_num;
            node.num = num; 
            data.push_back(node);
            int place = data.size() - 1;
            int parent = (place - 1) / 2;
            int level = (int)floor(log2(place + 1));
            if ( level % 2 == 0 ) { // minheap
                if ( data[place].graduate_num > data[parent].graduate_num ) { //maxheap
                    HeapData temp2 = data[parent];
                    data[parent] = data[place];
                    data[place] = temp2;
                    place = parent;
                    insert_maxheap (place);
                }
                
                else {
                    insert_minheap (place);
                }
            }

            else { // maxheap
                if ( data[place].graduate_num < data[parent].graduate_num ) { //minheap
                    HeapData temp2 = data[parent];
                    data[parent] = data[place];
                    data[place] = temp2;
                    place = parent;
                    insert_minheap (place);
                }
                
                else {
                    insert_maxheap (place);
                }
            }
            num++;
        }
        return;
    }

    void insert_maxheap (int place) {
        int parent = (place - 1) / 2;
        parent = (parent - 1) / 2;
        while ( parent >= 1 && data[place].graduate_num > data[parent].graduate_num ) {
            HeapData temp2 = data[place];
            data[place] = data[parent];
            data[parent] = temp2;
            place = parent;
            parent = (place - 1) / 2;
            parent = (parent - 1) / 2;
        } 
        return;
    }

    void insert_minheap (int place) {
        int parent = (place - 1) / 2;
        parent = (parent - 1) / 2;
        while ( parent >= 0 && data[place].graduate_num < data[parent].graduate_num ) {
            HeapData temp2 = data[place];
            data[place] = data[parent];
            data[parent] = temp2;
            place = parent;
            parent = (place - 1) / 2;
            parent = (parent - 1) / 2;
        } 
        return;
    }

    int left_bottom_idx(int n) {

        int level_nodes = 1;  // 每層節點數量
        int total_nodes = 0;  // 已經計算的節點數

        while (total_nodes + level_nodes < n) {
            total_nodes = total_nodes + level_nodes;
            level_nodes = level_nodes * 2;
        }

        return total_nodes;
    }

    void print_test() {
        for (int i = 0; i < data.size(); i++) {
            std::cout << data[i].num << "   ";
            std::cout << data[i].graduate_num << "/";
        }
        std::cout << "\n\n\n";
        return;
    }

    void delete_max(int place) { // 刪掉
        HeapData temp = data[place];
        data[place] = data[data.size() - 1];
        data[data.size() - 1] = temp;
        data.pop_back();
        return;
    }

    void rebuilt(int place, bool is_right) {
        int child = place * 2 + 1;
        int right = child + 1;
        if ( data[right].graduate_num > data[child].graduate_num ) {
            child = right;
        }
        if ( data[child].graduate_num > data[place].graduate_num) {
            HeapData temp = data[place];
            data[place] = data[child];
            data[child] = temp;
        }
        rebuilt_2 (place, is_right);
        return;
    }

    void rebuilt_2 (int place, bool is_right) {
        int level = (int)floor(log2(place + 1));
        int this_level_point = exp2(level + 1);
        HeapData max = data[place];
        int max_idx;
        int child;
        for (int i = 0; i < this_level_point; i++) {
            //print_test();
            int parent = place;
            if ( is_right ) {
                parent--;
            }
            child = 2 * parent + 1 + i;
            child = 2 * child + 1;
            while ( child <= data.size() ) {
                if ( data[child].graduate_num > data[place].graduate_num ) {
                    if ( max.graduate_num <= data[child].graduate_num ) {
                       max = data[child];
                       max_idx = child;
                    }
                }
                parent = child;
                child = 2 * parent + 1;
                child = 2 * child + 1;
            }
            child = (child - 1) / 2;
            int right = child + 1;
            if ( data[right].graduate_num > data[child].graduate_num ) {
                child = right;
            }
            if ( max.graduate_num <= data[child].graduate_num ) {
                max = data[child];
                max_idx = child;
            }
        }
        HeapData temp = data[place];
        data[place] = max;
        data[max_idx] = temp;
        return;
    }

};

void cut_term(std::string &line, std::vector<std::string> &term) {
    std::string temp = "";
    for (int i = 0; i < line.length(); i++) {
        char ch = line[i];
        if (ch == '\t') {   // 只有不是空的才存
            term.push_back(temp);
            temp = "";
        }

        else {
            temp = temp + ch;
        }
    }
    term.push_back(temp);
    return;
}

void to_int_student_num( std::string &term , std::string &temp) {
    for (int i = 0; i < term.length(); i++) {
        char ch = term[i];
        if (ch >= '0' && ch <= '9' ) {   // 只有不是空的才存
            temp = temp + ch;
        }
    }
    term = "";
    term = temp;
    return;
}

void load_order( std::vector<Data> &v, std::string &filename) {
    std::string line;
    std::ifstream infile(filename);
    std::getline(infile, line);
    std::getline(infile, line);
    std::getline(infile, line);
    while (std::getline(infile, line)) {
        std::vector<std::string> term;
        cut_term(line, term);
        Data d;
        d.num     = stoi(term[0]);
        d.school_name       = term[1];
        d.department_num     = stoi(term[2]);
        d.department_name     = term[3];
        d.Daytime      = term[4];
        d.level         = term[5];
        std::string temp;
        to_int_student_num( term[6] , temp);
        d.student_num     = stoi(term[6]);
        d.teacher_num    = stoi(term[7]);
        d.graduate_num     = stoi(term[8]);
        d.city_name     = term[9];
        d.system_type      = term[10];
        v.push_back(d);
    }
    return;
}

void print_order(std::vector<Data> &data) {
    for (int i = 0; i < data.size(); i++) {
        std::cout << data[i].num << "\t";
        std::cout << data[i].school_name << "\t";
        std::cout << data[i].department_num << "\t";
        std::cout << data[i].department_name << "\t";
        std::cout << data[i].Daytime << "\t";
        std::cout << data[i].level << "\t";
        std::cout << data[i].student_num << "\t";
        std::cout << data[i].teacher_num << "\t";
        std::cout << data[i].graduate_num << "\t";
        std::cout << data[i].city_name << "\t";
        std::cout << data[i].system_type << "\t";
        std::cout << "\n";
    }
}

void print_task1(MaxHeap &m) {
    std::cout << "<max heap>\n";
    HeapData root = m.data[0];
    std::cout << "root: [" << root.num << "] ";
    std::cout << root.graduate_num << "\n";
    int size = m.data.size() - 1;
    HeapData bottom = m.data[size];
    std::cout << "bottom: [" << bottom.num << "] ";
    std::cout << bottom.graduate_num << "\n";
    size = m.data.size();
    size = m.left_bottom_idx(size);
    HeapData left_bottom = m.data[size];
    std::cout << "leftmost bottom: [" << left_bottom.num << "] ";
    std::cout << left_bottom.graduate_num << "\n";
    return;
}

void print_task2(Deap &m) {
    std::cout << "<DEAP>\n";
    int size = m.data.size() - 1;
    HeapData bottom = m.data[size];
    std::cout << "bottom: [" << bottom.num << "] ";
    std::cout << bottom.graduate_num << "\n";
    size = m.data.size();
    size = m.left_bottom_idx(size);
    HeapData left_bottom = m.data[size];
    std::cout << "leftmost bottom: [" << left_bottom.num << "] ";
    std::cout << left_bottom.graduate_num << "\n";
    return;
}

void print_task3(minmax &m) {
    std::cout << "<MinMax>\n";
    HeapData root = m.data[0];
    std::cout << "root: [" << root.num << "] ";
    std::cout << root.graduate_num << "\n";
    int size = m.data.size() - 1;
    HeapData bottom = m.data[size];
    std::cout << "bottom: [" << bottom.num << "] ";
    std::cout << bottom.graduate_num << "\n";
    size = m.data.size();
    size = m.left_bottom_idx(size);
    HeapData left_bottom = m.data[size];
    std::cout << "leftmost bottom: [" << left_bottom.num << "] ";
    std::cout << left_bottom.graduate_num << "\n";
    return;
}

void print_task4(minmax &m, int place) {
    std::cout << "<MinMax>\n";
    HeapData root = m.data[place];
    std::cout << "root: [" << root.num << "] ";
    std::cout << root.graduate_num << "\n";
    return;
}

void task1( std::vector<Data> &data, MaxHeap &m) {
    m.data.clear();
    std::string filename;
    std::string file_number;
    std::cout << "\n";
    while (true) {
        std::cout << "Input a file number ([0] Quit): ";
        std::cin >> file_number;
        std::string filename = "input" + file_number + ".txt"; // 轉字串
        std::ifstream infile(filename); // 讀檔
        if ( file_number == "0" ) {
            std::cout << "\n";
            char ch = getchar();
            return;
        }
        if (!infile) {
            std::cout << "\n### input" << file_number << ".txt does not exist! ###\n\n";
            continue;
        }
        if ( infile ) {
            load_order(data, filename);
            m.built_maxheap(data);
            print_task1(m);
            break;
        }
    }
    std::cout << std::endl;
    char ch;
    ch = getchar();
    data.clear();
    return;
}

void task2( std::vector<Data> &data, Deap &d) {
    d.data.clear();
    d.reset();
    std::string filename;
    std::string file_number;
    std::cout << "\n";
    while (true) {
        std::cout << "Input a file number ([0] Quit): ";
        std::cin >> file_number;
        std::string filename = "input" + file_number + ".txt"; // 轉字串
        std::ifstream infile(filename); // 讀檔
        if ( file_number == "0" ) {
            std::cout << "\n";
            char ch = getchar();
            return;
        }
        if (!infile) {
            std::cout << "\n### input" << file_number << ".txt does not exist! ###\n\n";
            continue;
        }
        if ( infile ) {
            load_order(data, filename);
            d.built_deap(data);
            print_task2(d);
            break;
        }
    }
    std::cout << std::endl;
    char ch;
    ch = getchar();
    data.clear();
    return;
}

void task3( std::vector<Data> &data, minmax &d) {
    d.data.clear();
    std::string filename;
    std::string file_number;
    std::cout << "\n";
    while (true) {
        std::cout << "Input a file number ([0] Quit): ";
        std::cin >> file_number;
        std::string filename = "input" + file_number + ".txt"; // 轉字串
        std::ifstream infile(filename); // 讀檔
        if ( file_number == "0" ) {
            std::cout << "\n";
            char ch = getchar();
            return;
        }
        if (!infile) {
            std::cout << "\n### input" << file_number << ".txt does not exist! ###\n\n";
            continue;
        }
        if ( infile ) {
            load_order(data, filename);
            d.built_minmax(data);
            print_task3(d);
            break;
        }
    }
    std::cout << std::endl;
    char ch;
    ch = getchar();
    data.clear();
    return;
}

void task4(minmax &m) {
    int max = m.data.size();
    int k;
    std::cout << "Enter the value of K in [1,"<< max << "]: ";
    std::cin >> k;
    if ( k < 1 || k > max ) {
        std::cout << "### The value of K is out of range! ###\n";
        char ch = getchar();
        return;
    }

    else {
        m.print_test();
        for (int i = 0; i < k; i++) {
            bool is_right = true; //判斷是否在右邊idx = 2
            int place = 2;
            if ( m.data[1].graduate_num >= m.data[2].graduate_num ) {
                place = 1;
                is_right = false;
            }
            print_task4(m, place);
            m.delete_max(place);
            m.rebuilt(place, is_right);
        }
    }
    m.print_test();
    char ch = getchar();
}

void Start() {
    std::cout << "* Data Structures and Algorithms *\n";
    std::cout << "*** Heap Construction and Use ****\n";
    std::cout << "* 0. QUIT                        *\n";
    std::cout << "* 1. Build a max heap            *\n";
    std::cout << "* 2. Build a DEAP                *\n";
    std::cout << "***************************** ****\n";
    std::cout << "Input a choice(0, 1, 2, 3, 4): ";
    return;
}

int main() {
    std::vector<Data> data;
    MaxHeap m;
    Deap d;
    minmax min;
    int choice = 0;
    char ch;
    while (true) {
        Start();
        bool has_digit = false;
        bool invalid = false;
        while ((ch = getchar()) != '\n') {
            if (ch == ' ' || ch == '\t') {
                continue;
            } else if (ch >= '0' && ch <= '4') {
                if (has_digit) {
                    invalid = true; // 多個數字
                } else {
                    choice = ch - '0';
                    has_digit = true;
                }
            } else { // 非法字元
                invalid = true;
            }
        }
    // 處理非法輸入
        if (invalid || (!has_digit)) {
            std::cout << "\nCommand does not exist!" << std::endl << std::endl;
            continue;
        }
        if (choice == 0) {
            return 0;
        } else if (choice == 1) {
            task1(data, m);
        } else if (choice == 2) {
            task2(data, d);
        } 
         else if (choice == 3) {
            task3(data, min);
        } else if (choice == 4) {
            if (min.isEmpty()) {
                std::cout << "----- Execute Mission 3 first! -----\n\n";
                continue;
            }
            task4(min);
        }
    }
    return 0;
}
