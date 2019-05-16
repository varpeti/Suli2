#include "graphics.hpp"
#include "widgets.hpp"
#include "examplecheckbox.hpp"
#include "stattext.hpp"
#include "textbox.hpp"
#include <vector>
using namespace std;
using namespace genv;

void event_loop(vector<Widget*>& widgets) {
    event ev;
    int focus = -1;
    while(gin >> ev ) {
        if (ev.type == ev_mouse && ev.button==btn_left) {
            for (size_t i=0;i<widgets.size();i++) {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                        focus = i;
                }
            }
        }
        if (focus!=-1) {
            widgets[focus]->handle(ev);
        }
        for (size_t i=0;i<widgets.size();i++) {
            widgets[i]->draw();
        }
        gout << refresh;
    }
}


int main()
{
    gout.open(600,600);
    vector<Widget*> w;
    ExampleCheckBox * b1 = new ExampleCheckBox(10,10,30,30);
    ExampleCheckBox * b2 = new ExampleCheckBox(10,50,30,30);
    w.push_back(b1);
    w.push_back(b2);
    STATTEXT * s1 = new STATTEXT(50,30,"Alma");
    w.push_back(s1);
    TEXTBOX * t1 = new TEXTBOX(50,60,100,30);
    w.push_back(t1);
    event_loop(w);
    return 0;
}
