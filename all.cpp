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
    
    void delete_root() { // 刪掉根
        HeapData temp = data[0];
        data[0] = data[data.size() - 1];
        data[data.size() - 1] = temp;
        data.pop_back();
        rebuilt_maxheap(0);
    }

    void rebuilt_maxheap (int root) {
        int child = 2 * root + 1;
        if ( child < data.size() ) {
            int right_child = child + 1;
            if ( (right_child < data.size()) && (data[right_child].graduate_num > data[child].graduate_num )) {
                child = right_child;
            }
            if ( data[child].graduate_num > data[root].graduate_num ) {
                HeapData temp = data[root];
                data[root] = data[child];
                data[child] = temp;
                rebuilt_maxheap(child);
            }
        
        }
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


void task1( std::vector<Data> &data, MaxHeap &m) {
    std::string filename;
    std::string file_number;
    while (true) {
        std::cout << "Input a file number [0: quit]: ";
        std::cin >> file_number;
        std::string filename = "input" + file_number + ".txt"; // 轉字串
        std::ifstream infile(filename); // 讀檔
        if ( file_number == "0" ) {
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
    m.data.clear();
    return;
}

void task2( std::vector<Data> &data, Deap &d) {
    std::string filename;
    std::string file_number;
    while (true) {
        std::cout << "Input a file number [0: quit]: ";
        std::cin >> file_number;
        std::string filename = "input" + file_number + ".txt"; // 轉字串
        std::ifstream infile(filename); // 讀檔
        if ( file_number == "0" ) {
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
    d.data.clear();
    d.reset();
    return;
}

void Start() {
    std::cout << "* Data Structures and Algorithms *\n";
    std::cout << "*** Heap Construction and Use ****\n";
    std::cout << "* 0. QUIT                        *\n";
    std::cout << "* 1. Build a max heap            *\n";
    std::cout << "* 2. Build a DEAP                *\n";
    std::cout << "***************************** ****\n";
    std::cout << "Input a choice(0, 1, 2): ";
    return;
}

int main() {
    std::vector<Data> data;
    MaxHeap m;
    Deap d;
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
            std::cout << "Command does not exist!" << std::endl << std::endl;
            continue;
        }
        if (choice == 0) {
            return 0;
        } else if (choice == 1) {
            task1(data, m);
        } else if (choice == 2) {
            task2(data, d);
        } else if (choice == 3) {
            if (m.isEmpty()) {
                std::cout << "----- Execute Mission 1 first! -----\n\n";
                continue;
            }
            //task3(tree, data, change, size);
        } else if (choice == 4) {
            if (m.isEmpty()) {
                std::cout << "----- Execute Mission 1 first! -----\n\n";
                continue;
            }
            //task4(tree, change);
        }
    }
    return 0;
}
