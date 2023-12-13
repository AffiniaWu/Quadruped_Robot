#include "Robot.h"
#include "Config.h"
#include "PCA9685_servo.h"
#include "NVIC.h"
#include "Switch.h"
#include "Config.h"
#include "GPIO.h"
#include "UART.h"
#include "EXTI.h"

static void posture_init() {
    setServoDegree(1, 135);
    setServoDegree(3, 45);
    setServoDegree(5, 135);
    setServoDegree(7, 45);
    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);
    os_wait2(K_TMO, 50);
}


//初始化
void Robot_init() {
    //PCA9685模块初始化
    PCA9685_init();
    //初始化形态
    posture_init();
}


//扭呀扭
void Robot_dance() {
    u8 c=0,d=0,e=0;
    //初始化原始形态
    posture_init();
    //上方脚
    while(c<2) {
        setServoDegree(1, 180);
        setServoDegree(3, 90);
        setServoDegree(5, 180);
        setServoDegree(7, 90);

        os_wait2(K_TMO, 50);

        setServoDegree(1, 135);
        setServoDegree(3, 45);
        setServoDegree(5, 135);
        setServoDegree(7, 45);
        os_wait2(K_TMO, 50);
        c=c+1;
    }
    while(d<2) {
        setServoDegree(1, 90);
        setServoDegree(3, 0);
        setServoDegree(5, 90);
        setServoDegree(7, 0);
        os_wait2(K_TMO, 50);

        setServoDegree(1, 135);
        setServoDegree(3, 45);
        setServoDegree(5, 135);
        setServoDegree(7, 45);
        os_wait2(K_TMO, 50);
        d=d+1;
    }
//下方脚
    while(e<2) {
        setServoDegree(0, 90);
        setServoDegree(2, 90);
        setServoDegree(4, 90);
        setServoDegree(6, 90);

        os_wait2(K_TMO, 50);

        setServoDegree(0, 45);
        setServoDegree(2, 135);
        setServoDegree(4, 45);
        setServoDegree(6, 135);
        os_wait2(K_TMO, 50);
        e=e+1;
    }
}



//趴下
void Robot_down() {
    //初始化原始形态
    posture_init();

    setServoDegree(0, 90);
    setServoDegree(2, 90);
    setServoDegree(4, 90);
    setServoDegree(6, 90);
}
//站立
void Robot_up() {
    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);
}


//打招呼
void Robot_sayHi() {
		//初始化原始形态
    posture_init();
    setServoDegree(1, 180);
    setServoDegree(3, 0);

    setServoDegree(0, 180);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 135);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 180);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 135);

    os_wait2(K_TMO, 100);
    setServoDegree(1, 135);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 180);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 135);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 180);
    os_wait2(K_TMO, 50);
    setServoDegree(0, 135);
    os_wait2(K_TMO, 50);
    //恢复原样
    setServoDegree(0, 45);
    setServoDegree(3, 45);

}


//向前
void Robot_forward() {
    u8 i,j;
    //初始化前进姿态
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //运动模式
    for(j=0; j<5; j++) {
        //右脚先行
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45+i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(0, 90-i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 90+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);

        //交替到左脚先行
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135-i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(2, 90+i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 90-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);
    }
}

//向后
void Robot_backward() {

}

//向左
void Robot_left() {


}



//向右
void Robot_right() {
    u8 i,j;
    //初始化往右姿态
    setServoDegree(1, 90);
    setServoDegree(3, 90);
    setServoDegree(5, 90);
    setServoDegree(7, 90);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //运动模式
    for(j=0; j<5; j++) {
        //右前脚先行  0右前 4 左后
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45+i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //2 左前 6右后
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //0右前 4 左后
        for(i=1; i<=45; i++) {
            setServoDegree(0, 90-i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //2 左前 6右后
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 90+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);

        //交替到左前脚先行  2 左前 6右后
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135-i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //0右前 4 左后
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //2 左前 6右后
        for(i=1; i<=45; i++) {
            setServoDegree(2, 90+i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //0右前 4 左后
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 90-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);
    }
}

//旋转
void Robot_turn_around() {
    u8 i,j;
    //初始化右转旋转姿态
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //运动模式
    for(j=0; j<5; j++) {
        //左前脚先行  2 左前 6右后
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //右脚  0右前 4 左后
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //左脚  2 左前 6右后
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //右脚  0右前 4 左后
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);
    }
}

//停止
void Robot_stop() {
    u8 i;
    //初始化原始形态
    posture_init();

    //逐步递减，不要太急速
    for(i=1; i<=45; i++) {
        setServoDegree(1,135-i);
        setServoDegree(5,135-i);
        setServoDegree(3, 45+i);
        setServoDegree(7, 45+i);
        os_wait2(K_TMO, 4);
    }
    os_wait2(K_TMO, 50);
    for(i=1; i<=45; i++) {
        setServoDegree(0, 45-i);
        setServoDegree(2, 135+i);
        setServoDegree(4, 45-i);
        setServoDegree(6, 135+i);
        os_wait2(K_TMO, 4);
    }
}