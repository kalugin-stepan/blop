#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct Frame {
    char** frame_data;
    unsigned w;
    unsigned h;
    Frame() {
        ifstream inp("input.txt");
        inp >> w;
        inp >> h;
        frame_data = new char*[h];
        for (unsigned i = 0; i < h; i++) {
            frame_data[i] = new char[w];
            for (unsigned j = 0; j < w; j++) {
                inp >> frame_data[i][j];
            }
        }
    }
    ~Frame() {
        delete[] frame_data;
    }
};

unsigned find_obj_S(Frame* frame, unsigned x, unsigned y);
void print_frame(Frame* frame);

int main() {
    Frame frame;

    for (unsigned i = 0; i < frame.h; i++) {
        for (unsigned j = 0; j < frame.w; j++) {
            if (frame.frame_data[i][j] != '#') continue;
            cout << find_obj_S(&frame, j, i) << endl;
            print_frame(&frame);
        }
    }
}

void print_frame(Frame* frame) {
    for (unsigned i = 0; i < frame->h; i++) {
        for (unsigned j = 0; j < frame->w; j++) {
            cout << frame->frame_data[i][j] << ' ';
        }
        cout << endl;
    }
}

unsigned find_obj_S(Frame* frame, unsigned x, unsigned y) {
    if (x >= frame->w || y >= frame->h) return 0;
    unsigned S = 1;
    if (frame->frame_data[y][x] != '#') return 0;
    frame->frame_data[y][x] = '~';
    S += find_obj_S(frame, x+1, y);
    S += find_obj_S(frame, x-1, y);
    S += find_obj_S(frame, x, y+1);
    return S;
}