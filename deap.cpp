class Deap {
   public:
    std::vector<HeapData> data;

    Deap() {
        HeapData dummy;
        data.push_back(dummy);
    }

    bool isEmpty() {
        if ( data.size() <= 1) {
            return true;
        }
        return false;
    }

    bool is_minheap(int idx, int &level) {
        level = (int)floor(log2(idx + 1));
        int first_idx = exp2(level);
        int half = first_idx / 2;
        if ( idx < first_idx + half ) {
            return true;
        }
        return false;
    }


    int corresponding_point(bool is_minheep, int level, int idx) {
        if ( idx == 1 || idx == 2) {
            return idx;
        }
        int displacement = exp2(level - 1);
        if ( is_minheep ) {
            int parent = (idx + displacement - 1) / 2;
            //std::cout << parent << "p\n";
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
            node.num = d[i].num; 
            data.push_back(node);
            int place = data.size() - 1;
            bool is_min = is_minheap(place, level);
            if ( is_min ) { // minheap
                int correspond_point = corresponding_point(is_min, level, place);
                if ( data[correspond_point].graduate_num > data[place].graduate_num ) { // maxheap
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
                if ( data[correspond_point].graduate_num < data[place].graduate_num ) { // minheap
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
};
