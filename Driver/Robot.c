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


//��ʼ��
void Robot_init() {
    //PCA9685ģ���ʼ��
    PCA9685_init();
    //��ʼ����̬
    posture_init();
}


//ŤѽŤ
void Robot_dance() {
    u8 c=0,d=0,e=0;
    //��ʼ��ԭʼ��̬
    posture_init();
    //�Ϸ���
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
//�·���
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



//ſ��
void Robot_down() {
    //��ʼ��ԭʼ��̬
    posture_init();

    setServoDegree(0, 90);
    setServoDegree(2, 90);
    setServoDegree(4, 90);
    setServoDegree(6, 90);
}
//վ��
void Robot_up() {
    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);
}


//���к�
void Robot_sayHi() {
		//��ʼ��ԭʼ��̬
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
    //�ָ�ԭ��
    setServoDegree(0, 45);
    setServoDegree(3, 45);

}


//��ǰ
void Robot_forward() {
    u8 i,j;
    //��ʼ��ǰ����̬
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //�˶�ģʽ
    for(j=0; j<5; j++) {
        //�ҽ�����
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

        //���浽�������
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

//���
void Robot_backward() {

}

//����
void Robot_left() {


}



//����
void Robot_right() {
    u8 i,j;
    //��ʼ��������̬
    setServoDegree(1, 90);
    setServoDegree(3, 90);
    setServoDegree(5, 90);
    setServoDegree(7, 90);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //�˶�ģʽ
    for(j=0; j<5; j++) {
        //��ǰ������  0��ǰ 4 ���
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45+i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //2 ��ǰ 6�Һ�
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //0��ǰ 4 ���
        for(i=1; i<=45; i++) {
            setServoDegree(0, 90-i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //2 ��ǰ 6�Һ�
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 90+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);

        //���浽��ǰ������  2 ��ǰ 6�Һ�
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135-i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //0��ǰ 4 ���
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //2 ��ǰ 6�Һ�
        for(i=1; i<=45; i++) {
            setServoDegree(2, 90+i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);
        //0��ǰ 4 ���
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 90-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);
    }
}

//��ת
void Robot_turn_around() {
    u8 i,j;
    //��ʼ����ת��ת��̬
    setServoDegree(1, 180);
    setServoDegree(3, 0);
    setServoDegree(5, 180);
    setServoDegree(7, 0);

    setServoDegree(0, 45);
    setServoDegree(2, 135);
    setServoDegree(4, 45);
    setServoDegree(6, 135);

    //�˶�ģʽ
    for(j=0; j<5; j++) {
        //��ǰ������  2 ��ǰ 6�Һ�
        for(i=1; i<=45; i++) {
            setServoDegree(2, 135+i);
            setServoDegree(6, 135+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //�ҽ�  0��ǰ 4 ���
        for(i=1; i<=45; i++) {
            setServoDegree(0, 45-i);
            setServoDegree(4, 45-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //���  2 ��ǰ 6�Һ�
        for(i=1; i<=45; i++) {
            setServoDegree(2, 180-i);
            setServoDegree(6, 180-i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 1);

        //�ҽ�  0��ǰ 4 ���
        for(i=1; i<=45; i++) {
            setServoDegree(0, 0+i);
            setServoDegree(4, 0+i);
            os_wait2(K_TMO, 1);
        }
        os_wait2(K_TMO, 20);
    }
}

//ֹͣ
void Robot_stop() {
    u8 i;
    //��ʼ��ԭʼ��̬
    posture_init();

    //�𲽵ݼ�����Ҫ̫����
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