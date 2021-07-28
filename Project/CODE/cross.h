#ifndef CORSS_H
#define CORSS_H

enum cross_type_e {
    CROSS_NONE = 0,     // 非十字模式
    CROSS_BEGIN,        // 找到左右两个L角点
    CROSS_IN,           // 两个L角点很近，即进入十字内部(此时切换远线控制)
    CROSS_NUM,
};

extern enum cross_type_e cross_type;

extern const char *cross_type_name[CROSS_NUM];

void check_cross();

void run_cross();

void draw_cross();

void cross_farline();

#endif // CORSS_H