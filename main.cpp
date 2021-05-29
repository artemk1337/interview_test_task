#include "main.h"


void print_array(vector<vector<INT>>& array) {
    for (vector<INT>& row : array) {
        for (INT &c : row)
            cout << c;
        cout << endl;
    }
    cout << endl;
}


RECT_STRUCT apply_rect_params(RECT_STRUCT rect, INT max_rect, INT x, INT y, INT x_shift, INT y_shift) {
    rect.max_rect = max_rect;
    rect.x = x;
    rect.y = y;
    rect.x_shift = x_shift;
    rect.y_shift = y_shift;
    return rect;
}


void progress_bar(INT curr_val, INT max_val) {
    cout << "\r" << static_cast<double>(curr_val) / static_cast<double>(max_val) * 100 << "%";
}


RECT_STRUCT find_max_rect_in_row(vector<INT>& row) {

    RECT_STRUCT rect;
    rect.max_rect = 0;
    stack<INT> indexes;

    INT idx = 0;
    while (idx < row.size()) {
        if (indexes.empty() || row[indexes.top()] <= row[idx])
            indexes.push(idx++);  // add index, if current value >= prev value
        else {
            INT prev_index = indexes.top();
            INT prev_value = row[prev_index];
            indexes.pop();

            INT prev_rect = indexes.empty() ? prev_value * idx : prev_value * (idx - indexes.top() - 1);
            if (prev_rect > rect.max_rect)
                rect = apply_rect_params(rect, prev_rect, prev_index, 0,
                                         idx - prev_index - 1,
                                         prev_value - 1);
        }
    }

    // reached the end of row
    // clearing and computing the remaining stack
    while (!indexes.empty())
    {
        INT prev_index = indexes.top();
        INT prev_value = row[prev_index];
        indexes.pop();

        INT prev_rect = indexes.empty() ? prev_value * idx : prev_value * (idx - indexes.top() - 1);
        if (prev_rect > rect.max_rect)
            rect = apply_rect_params(rect, prev_rect, prev_index, 0,
                                     idx - prev_index - 1,
                                     prev_value - 1);
    }
    return rect;
}


/*
 * 0 1 1 0  ➔  0 1 1 0
 * 1 0 1 0  ➔  1 0 2 0
 * 1 1 1 1  ➔  2 1 3 1
 * 0 0 0 1  ➔  0 0 0 2
*/
void prepare_array(vector<vector<INT>>& array) {
    for (INT y = 1; y < array.size(); y++) {
        for (INT x = 0; x < array[y].size(); x++) {
            if (array[y][x])
                array[y][x] = array[y-1][x] + 1;
        }
    }
}


string algorithm(vector<vector<INT>>& array) {
    RECT_STRUCT max_rect, rect;

    prepare_array(array);  // calculate max len of columns
    // print_array(array);
    max_rect = find_max_rect_in_row(array[0]);  // calculate first row
    for (INT y = 1; y < array.size(); y++) {
        rect = find_max_rect_in_row(array[y]);
        rect.y = y;
        if (max_rect.max_rect < rect.max_rect)
            max_rect = rect;
        // progress_bar(y, array.size());
    }
    return "\nS: " + to_string(max_rect.max_rect) + "\n(x1, y1): (" +
           to_string(max_rect.x) + ", "
           + to_string(max_rect.y - max_rect.y_shift) + ")\n(x2, y2): (" +
           to_string(max_rect.x + max_rect.x_shift) + ", "
           + to_string(max_rect.y) + ")";;
}


int main(int argc, char **argv) {
    if (argc != 1)
        cerr << "Argc != 0" << endl;

    ifstream filemap("../map.txt");  // open file

    // read file
    vector<vector<INT>> array;
    string line;
    while (getline (filemap, line)) {
        vector<INT> line_vec;
        for (char& c : line)
            line_vec.push_back(c - 48);
        array.push_back(line_vec);
    }
    filemap.close();

    // print_array(array);

    cout << algorithm(array) << endl;

    return 0;
}

