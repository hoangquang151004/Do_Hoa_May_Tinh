#include "glut.h"
#include <cmath>
#include <stdio.h>

// Camera position & angles
float camX = 0.0f, camY = 2.0f, camZ = 7.0f;
float angleY = 0.0f; // Xoay ngang (trái/phải)
float angleX = 0.0f; // Xoay dọc (lên/xuống)

// Tốc độ di chuyển và xoay
float moveSpeed = 0.2f;
float rotateSpeed = 0.05f;

bool isCeilingLightOn = false; // điều khiển bật/tắt
bool isLight_dir = false;
bool isLight_cutoff = false;
bool isCustomSpotlightOn = true;
GLfloat spotlightPos[3] = { 0.0f,4.9,0.0f };     // vị trí đèn
GLfloat spotlightTarget[3] = { 0.0f, 0.0f, 0.0f };  // nơi chiếu tới
GLfloat spotlightCutoff = 30.0f;                   // góc chiếu


bool isAmbientLightOn = false;



void vexy() {
    glLineWidth(1.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);
    glEnd();
    glLineWidth(1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);
    glEnd();
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glEnd();
}
void drawRoom() {
    // Sàn
    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8); // Màu xám
    glTranslatef(0, 0, 0);
    glScalef(10, 0.2, 10);
    glutSolidCube(1.0);
    glPopMatrix();

    // Tường trái
    glPushMatrix();
    glColor3f(0.9, 0.6, 0.6); // Hồng nhạt
    glTranslatef(-5, 2.5, 0);
    glScalef(0.2, 5, 10);
    glutSolidCube(1.0);
    glPopMatrix();

    // Tường phải
    glPushMatrix();
    glColor3f(0.9, 0.6, 0.6); // Hồng nhạt
    glTranslatef(5, 2.5, 0);
    glScalef(0.2, 5, 10);
    glutSolidCube(1.0);
    glPopMatrix();

    // Tường sau
    glPushMatrix();
    glColor3f(0.6, 0.9, 0.6); // Xanh nhạt
    glTranslatef(0, 2.5, -5);
    glScalef(10, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Tường trước
    glPushMatrix();
    glColor3f(0.6, 0.9, 0.6); // Xanh nhạt
    glTranslatef(0, 2.5, 5);
    glScalef(10, 5, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Trần nhà
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.9); // Màu trắng nhạt
    glTranslatef(0, 5, 0); // Đặt ở độ cao y = 5
    glScalef(10, 0.2, 10); // Kích thước tương tự sàn
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawStudyTable(float x, float y, float z) {
    glPushMatrix();
    glTranslated(x, y, z);
    // Mặt bàn
    glPushMatrix();
    glColor3f(0.7f, 0.4f, 0.1f); // Màu gỗ
    glTranslatef(0.0f, 2.4f, 0.0f);
    glScalef(4.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Các chân bàn (4 chân)
    float legHeight = 2.4f;
    float legOffsetX = 1.8f;
    float legOffsetZ = 0.8f;
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glColor3f(0.5f, 0.3f, 0.1f);
            glTranslatef(i * legOffsetX, legHeight / 2.0f, j * legOffsetZ);
            glScalef(0.2f, legHeight, 0.2f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }
    // Ngăn kéo bên phải
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.8f); // Xanh dương
    glTranslatef(1.2f, 2.2f, 0.0f);
    glScalef(1.0f, 0.5f, 1.2f);
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();
}

void drawComputer(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z); // Dịch toàn bộ máy tính tới vị trí (x, y, z)

    // ======= MÀN HÌNH =========
    glPushMatrix();
    glColor3f(0.1f, 0.1f, 0.1f); // Viền đen
    glTranslatef(0.0f, 0.8f, -0.7f);
    glScalef(1.5f, 1.0f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Màn hình hiển thị
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.8f); // Xanh dương
    glTranslatef(0.0f, 0.8f, -0.63f);
    glScalef(1.3f, 0.8f, 0.01f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Chân màn hình
    glPushMatrix();
    glColor3f(0.3f, 0.4f, 0.3f);
    glTranslatef(0.0f, 0.3f, -0.7f);
    glScalef(0.1f, 0.3f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Đế màn hình
    glPushMatrix();
    glColor3f(0.2f, 0.6f, 0.2f);
    glTranslatef(0.0f, 0.1f, -0.7f);
    glScalef(0.8f, 0.05f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // ======= BÀN PHÍM =========
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glTranslatef(0.0f, 0.15f, -0.2f);
    glScalef(1.2f, 0.05f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // ======= CHUỘT =========
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.8f, 0.15f, -0.2f);
    glScalef(0.2f, 0.05f, 0.3f);
    glutSolidSphere(1.0f, 20, 20);
    glPopMatrix();

    // ======= THÂN MÁY =========
    glPushMatrix();
    glColor3f(0.15f, 0.15f, 0.15f);
    glTranslatef(2.2f, -1.8f, 0.0f); // thấp hơn gốc máy tính
    glScalef(0.6f, 1.2f, 1.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix(); // Kết thúc việc dịch toàn bộ máy tính
}

void drawChairStudent(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z); // Đặt ghế vào đúng vị trí

    // Mặt ghế
    glPushMatrix();
    glColor3f(0.7, 0.4, 0.1); // Màu gỗ
    glTranslatef(0.0f, 1.5f, 0.0f);
    glScalef(2.0f, 0.2f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // 4 chân ghế
    float d = 1.5f;
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            glPushMatrix();
            glColor3f(0.5f, 0.3f, 0.1f);
            glTranslatef(i * d * 0.5f, 0.75f, j * d * 0.5f);
            glScalef(0.2f, 1.5f, 0.2f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }

    // Lưng tựa
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.1f);
    glTranslatef(0.0f, 2.4f, -0.9f);
    glScalef(2.0f, 1.6f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}


void drawBookStack(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);  // Dịch toàn bộ chồng sách tới vị trí (x, y, z)
    glRotatef(90, 0, 0, 1);
    float thickness = 0.2f;
    float baseY = 0.0f;

    for (int i = 0; i < 3; ++i) {
        glPushMatrix();

        // Dịch từng quyển lên cao dần
        glTranslatef(0.0f, baseY + i * thickness, 0.0f);

        // Màu sắc khác nhau cho mỗi quyển
        switch (i) {
        case 0: glColor3f(1.0f, 0.0f, 0.0f); break; // đỏ
        case 1: glColor3f(0.0f, 1.0f, 0.0f); break; // xanh lá
        case 2: glColor3f(0.0f, 0.0f, 1.0f); break; // xanh dương
        case 3: glColor3f(1.0f, 1.0f, 0.0f); break; // vàng
        case 4: glColor3f(1.0f, 0.0f, 1.0f); break; // tím
        }

        // Kích thước hơi khác nhau cho mỗi quyển
        float scaleX = 1.0f + 0.05f * (i % 2);
        float scaleZ = 0.6f - 0.05f * (i % 3);
        glScalef(scaleX, thickness, scaleZ);

        // Vẽ quyển sách
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    glPopMatrix();
}

void drawLamp(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);  // Dịch đến vị trí đặt đèn
    glScalef(0.5, 0.5, 0.5);
    // ===== ĐẾ ĐÈN =====
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f); // Xám
    glScaled(0.5, 0.5, 0.5);
    glTranslatef(0.0f, 0.05f, 0.0f);
    glRotatef(-90, 1, 0, 0);  // Quay để đế nằm ngang
    GLUquadric* base = gluNewQuadric();
    gluDisk(base, 0.0, 1.0, 30, 1);  // Đế hình tròn
    glPopMatrix();

    // ===== CÁNH TAY THỨ NHẤT =====
    glPushMatrix();
    glColor3f(0.0f, 0.6f, 0.8f); // Xanh dương nhạt
    glTranslatef(0.0f, 0.5f, 0.0f); // Dịch lên
    glScalef(0.1f, 1.0f, 0.1f);     // Gầy dài
    glutSolidCube(1.0f);
    glPopMatrix();

    // ===== KHỚP NỐI =====
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Vàng
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.1f, 20, 20);
    glPopMatrix();

    // ===== CÁNH TAY THỨ HAI =====
    glPushMatrix();
    glColor3f(0.0f, 0.6f, 0.8f);
    glTranslatef(0.0f, 1.5f, 0.0f);
    glRotatef(45, 0, 0, 1);  // Nghiêng sang phải
    glTranslatef(-0.38f, 0.0f, 0.0f);
    glScalef(0.1f, 0.7f, 0.1f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // ===== CHỤP ĐÈN (hình nón) =====
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f); // Đen
    glTranslatef(-1.0f, 1.2f, 0.0f);
    glRotatef(135, 0, 0, 1); // Hướng xuống
    glRotatef(90, 1, 0, 0);  // Hướng theo trục z
    GLUquadric* cone = gluNewQuadric();
    gluCylinder(cone, 0.3f, 0.0f, 0.6f, 20, 10);
    glPopMatrix();

    // ===== BÓNG ĐÈN =====
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.8f); // Vàng nhạt
    glTranslatef(-0.6f, 1.55f, 0.0f);
    glutSolidSphere(0.1f, 20, 20);
    glPopMatrix();

    glPopMatrix(); // Kết thúc toàn bộ đèn
}

void drawPenBox(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z); // Di chuyển đến vị trí

    // ===== Vẽ thân hộp =====
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.0f); // Màu nâu
    glScalef(0.3f, 1.0f, 0.3f);  // Kích thước hộp
    glutSolidCube(1.0f);
    glPopMatrix();

    // ===== Các cây bút =====
    GLUquadric* quad = gluNewQuadric();

    // Bút 1
    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f); // Đỏ
    glTranslatef(-0.1f, 0.2f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.03, 0.03, 0.5, 12, 3);
    glPopMatrix();

    // Bút 2
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 1.0f); // Xanh lá
    glTranslatef(0.0f, 0.2f, 0.05f);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.03, 0.03, 0.6, 12, 3);
    glPopMatrix();

    // Bút 3
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 1.0f); // Xanh dương
    glTranslatef(0.1f, 0.2f, -0.05f);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.03, 0.03, 0.55, 12, 3);
    glPopMatrix();

    // Đầu bút (mũi nhọn) - cho bút 1
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f); // Đen
    glTranslatef(-0.1f, 0.7f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.03, 0.0, 0.1, 10, 2);
    glPopMatrix();

    glPopMatrix(); // Kết thúc toàn bộ hộp bút
}

void drawBed(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // ===== Khung giường =====
    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.1f); // Màu gỗ
    glScalef(4.0f, 0.5f, 2.0f);   // Dài, cao, rộng
    glutSolidCube(1.0);
    glPopMatrix();

    // ===== Nệm =====
    glPushMatrix();
    glColor3f(0.9f, 0.9f, 0.9f); // Màu trắng
    glTranslatef(0.0f, 0.3f, 0.0f); // Lên trên khung giường
    glScalef(3.8f, 0.3f, 1.8f);
    glutSolidCube(1.0);
    glPopMatrix();

    // ===== Chăn =====
    glPushMatrix();
    glColor3f(0.2f, 0.6f, 1.0f); // Màu xanh dương nhạt
    glTranslatef(0.0f, 0.45f, 0.2f); // Trên nệm, lệch chút về cuối giường
    glScalef(3.8f, 0.1f, 1.2f);
    glutSolidCube(1.0);
    glPopMatrix();

    // ===== Gối 1 =====
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.8f); // Màu kem
    glTranslatef(-0.7f, 0.5f, -0.6f);
    glScalef(1.2f, 0.2f, 0.6f);
    glutSolidCube(1.0);
    glPopMatrix();

    // ===== Gối 2 =====
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.8f); // Màu kem
    glTranslatef(0.7f, 0.5f, -0.6f);
    glScalef(1.2f, 0.2f, 0.6f);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix(); // Kết thúc toàn bộ giường
}

void drawWardrobe(int a, float x, float y, float z) {
    glPushMatrix();
    glRotated(a, 0, 1, 0);
    glTranslatef(x, y, z);
    GLUquadric* quad;
    quad = gluNewQuadric();

    // ===== Thân tủ =====
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f); // Màu nâu gỗ
    glScalef(2.0f, 4.0f, 1.0f); // Dài, cao, rộng
    glutSolidCube(1.0f);
    glPopMatrix();

    // ===== Cánh cửa trái =====
    glPushMatrix();
    glColor3f(0.65f, 0.35f, 0.1f); // Màu gỗ sáng hơn
    glTranslatef(-0.5f, 0.0f, 0.51f); // Dịch ra phía trước
    glScalef(0.95f, 3.9f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // ===== Cánh cửa phải =====
    glPushMatrix();
    glColor3f(0.65f, 0.35f, 0.1f);
    glTranslatef(0.5f, 0.0f, 0.51f);
    glScalef(0.95f, 3.9f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tay nắm trái
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f); // Vàng
    glTranslatef(-0.3f, 0.0f, 0.56f);
    glRotatef(-90, 1, 0, 0); // Quay trục để dựng đứng
    gluCylinder(quad, 0.03, 0.03, 0.1, 16, 16);
    glPopMatrix();

    // Tay nắm phải
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(0.3f, 0.0f, 0.56f);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.03, 0.03, 0.1, 16, 16);
    glPopMatrix();

    glPopMatrix(); // Kết thúc tủ
}

void drawPlantPot(float x, float y, float z) {
    GLUquadric* quad = gluNewQuadric();

    // Thân chậu cây (hình trụ)
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.6f, 0.3f, 0.0f); // Nâu đất
    glRotatef(-90, 1, 0, 0); // Xoay để hình trụ đứng lên
    gluCylinder(quad, 0.3, 0.25, 0.3, 30, 30);
    glPopMatrix();

    // Cây thân (hình trụ nhỏ)
    glPushMatrix();
    glTranslatef(x, y + 0.3, z);
    glColor3f(0.4f, 0.2f, 0.0f); // Màu thân cây
    glRotatef(-90, 1, 0, 0);
    gluCylinder(quad, 0.05, 0.05, 0.5, 16, 16);
    glPopMatrix();

    // Lá cây (hình cầu màu xanh)
    glPushMatrix();
    glTranslatef(x, y + 0.8, z);
    glColor3f(0.0f, 0.6f, 0.0f); // Xanh lá
    glutSolidSphere(0.25, 20, 20);
    glPopMatrix();

    gluDeleteQuadric(quad);
}

void drawAirConditioner(float x, float y, float z) {
    // Vị trí chung
    glPushMatrix();
    glTranslatef(x, y, z);

    // Thân điều hòa
    glPushMatrix();
    glColor3f(0.9f, 0.9f, 0.9f); // Màu trắng xám
    glScalef(2.5f, 0.6f, 0.6f);  // Kích thước thân
    glutSolidCube(1.0f);
    glPopMatrix();

    // Mặt trước (khe gió)
    for (int i = -2; i <= 2; ++i) {
        glPushMatrix();
        glColor3f(0.6f, 0.6f, 0.6f); // Màu xám
        glTranslatef(i * 0.2f, -0.15f, 0.31f); // Từng khe gió
        glScalef(0.15f, 0.05f, 0.02f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Đèn LED nhỏ
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f); // Màu xanh lá
    glTranslatef(0.7f, 0.15f, 0.31f);
    glutSolidSphere(0.03f, 10, 10);
    glPopMatrix();

    glPopMatrix(); // Kết thúc điều hòa
}

void drawWindow(int a, float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(a, 0, 1, 0);
    // Khung ngoài cửa sổ
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f); // Màu gỗ
    glScalef(2.0f, 2.0f, 0.1f);     // Tấm lớn
    glutSolidCube(1.0f);
    glPopMatrix();

    // Ô kính bên trái
    glPushMatrix();
    glColor3f(0.6f, 0.8f, 1.0f); // Màu xanh nhạt
    glTranslatef(-0.5f, 0.5f, 0.06f);
    glScalef(0.8f, 0.8f, 0.02f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6f, 0.8f, 1.0f);
    glTranslatef(0.5f, 0.5f, 0.06f);
    glScalef(0.8f, 0.8f, 0.02f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6f, 0.8f, 1.0f);
    glTranslatef(-0.5f, -0.5f, 0.06f);
    glScalef(0.8f, 0.8f, 0.02f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.6f, 0.8f, 1.0f);
    glTranslatef(0.5f, -0.5f, 0.06f);
    glScalef(0.8f, 0.8f, 0.02f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix(); // Kết thúc cửa sổ
}

void drawDoor(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Khung cửa (bao quanh thân cửa)
    glPushMatrix();
    glColor3f(0.4f, 0.2f, 0.1f); // Màu nâu đậm
    glScalef(1.2f, 2.2f, 0.1f);  // Khung lớn hơn thân cửa
    glutSolidCube(1.0f);
    glPopMatrix();

    // Thân cửa
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.1f); // Màu gỗ sáng hơn
    glTranslatef(0.0f, 0.0f, 0.06f); // Nhô ra một chút
    glScalef(1.0f, 2.0f, 0.02f);    // Thân cửa chính
    glutSolidCube(1.0f);
    glPopMatrix();

    // Tay nắm cửa (hình cầu)
    glPushMatrix();
    glColor3f(1.0f, 0.84f, 0.0f); // Màu vàng
    glTranslatef(0.35f, -0.2f, 0.1f); // Vị trí bên phải
    glutSolidSphere(0.05, 16, 16);
    glPopMatrix();

    glPopMatrix(); // Kết thúc cửa
}

void drawCylinder(float radius, float height, int slices = 20) {
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, radius, radius, height, slices, 1);
    gluDeleteQuadric(quad);
}

void drawFan(float x, float y, float z, float angle) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Trục đứng
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.8f);
    glTranslatef(0.0f, 1.0f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    drawCylinder(0.05f, 1.0f);
    glPopMatrix();

    // Thân quạt
    glPushMatrix();
    glColor3f(0.8f, 0.2f, 0.2f);
    glTranslatef(0.0f, 1.1f, 0.0f);
    glutSolidSphere(0.15f, 20, 20);

    // Cánh quạt (xoay được)
    glRotatef(angle, 0, 1, 0); // xoay cánh theo góc angle

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glRotatef(i * 120, 0, 1, 0);
        glTranslatef(0.25f, 0.0f, 0.0f);
        glScalef(0.5f, 0.05f, 0.1f);
        glColor3f(0.6f, 0.6f, 1.0f);
        glutSolidCube(1.5f);
        glPopMatrix();
    }

    glPopMatrix(); // kết thúc thân và cánh

    glPopMatrix();
}

void drawBookshelf(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Cột trái
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f); // nâu gỗ
    glTranslatef(-1.0f, 0.7f, 0.0f);
    glScalef(0.1f, 1.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Cột phải
    glPushMatrix();
    glColor3f(0.55f, 0.27f, 0.07f);
    glTranslatef(1.0f, 0.7f, 0.0f);
    glScalef(0.1f, 1.0f, 0.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Các tầng kệ
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glColor3f(0.6f, 0.4f, 0.2f);
        glTranslatef(0.0f, 0.2f + i * 1.0f, 0.0f);
        glScalef(2.2f, 0.1f, 0.5f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    // Một vài quyển sách trên tầng 2
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glColor3f(0.2f + 0.2f * i, 0.3f + 0.1f * i, 0.8f - 0.1f * i);
        glTranslatef(-0.9f + i * 0.3f, 0.55f, 0.0f);
        glScalef(0.2f, 0.6f, 0.4f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    glPopMatrix();
}

void drawDeskCalendar(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Phần đáy tam giác (hình hộp phẳng nằm dưới)
    glPushMatrix();
    glColor3f(0.6f, 0.3f, 0.0f);  // Màu nâu
    glTranslatef(0.0f, 0.06f, 0.0f);
    glScalef(1.5f, 0.1f, 0.5f);
    glutSolidCube(0.5f);
    glPopMatrix();

    // Phần mặt trước tam giác (lịch giấy)
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.8f);  // Màu giấy
    glTranslatef(0.0f, 0.2f, -0.25f);
    glRotatef(-60, 1, 0, 0);  // nghiêng mặt trước
    glScalef(1.5f, 1.0f, 0.1f);
    glutSolidCube(0.5f);
    glPopMatrix();

    glPopMatrix();
}

void drawPicture(float x, float y, float z) {
    glPushMatrix();
    glRotated(-180, 0, 1, 0);
    // Vẽ khung tranh
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(2.0f, 1.5f, 0.05f); // Khung tranh
    glColor3f(0.4f, 0.2f, 0.0f); // Màu nâu khung gỗ
    glutSolidCube(1.0f);
    glPopMatrix();

    // Vẽ nội dung tranh (mặt bên trong khung)
    glPushMatrix();
    glTranslatef(x, y, z + 0.03f); // Đẩy lên một chút để không bị ăn vào khung
    glScalef(1.8f, 1.3f, 0.01f); // Nhỏ hơn khung
    glColor3f(0.2f, 0.6f, 0.9f); // Màu nội dung tranh
    glutSolidCube(1.0f);
    glPopMatrix();
    glPopMatrix();
}

void drawCarpet(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(3.0f, 0.02f, 2.0f); // Dài x rộng x độ dày
    glColor3f(0.8f, 0.1f, 0.1f); // Màu đỏ thảm
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawCeilingBulb(float x, float y, float z) {
    GLfloat emission[] = { 1.0, 1.0, 0.8, 1.0 }; // màu vàng nhạt
    GLfloat noEmission[] = { 0.0, 0.0, 0.0, 1.0 };

    glPushMatrix();
    glTranslatef(x, y, z);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glColor3f(1.0f, 1.0f, 0.7f);
    glutSolidSphere(0.1, 20, 20);
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glPopMatrix();
}


// Thiet lap nguon sáng 

void setupCeilingLight() {
    if (isCeilingLightOn) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE); // quan trọng khi dùng glScalef

        // Đây là đèn định hướng từ trên xuống
        GLfloat lightPos[] = { 0.0,4.9,0,0 };
        GLfloat lightDir[] = { 0.0f, 0.0f, 0.0f, 0.0f }; // w = 0 → hướng chiếu

        // Ánh sáng sáng rõ nhưng mềm
        GLfloat diffuse[] = { 1.2f, 1.2f, 1.0f, 1.0f }; // ánh sáng chính
        GLfloat ambient[] = { 0.4f, 0.4f, 0.3f, 1.0f }; // ánh sáng môi trường
        GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // phản xạ

        glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightDir);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

    }
    else {
        glDisable(GL_LIGHT0);
    }
}

void setupCeilingDir() {
    if (isLight_dir) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        glEnable(GL_NORMALIZE); // quan trọng khi dùng glScalef

        // Đây là đèn định hướng từ trên xuống
        GLfloat lightPos[] = { 0.0, 4.9, 0.0, 1.0 }; // w = 1.0 ⇒ điểm (spotlight)
        GLfloat spotDir[] = { 0, -1, 0 };     // chiếu xuống theo trục Y âm

        // Ánh sáng sáng rõ nhưng mềm
        GLfloat diffuse[] = { 1.2f, 1.2f, 1.0f, 1.0f }; // ánh sáng chính
        GLfloat ambient[] = { 0.4f, 0.4f, 0.3f, 1.0f }; // ánh sáng môi trường
        GLfloat specular[] = { 0.5f, 0.5f, 0.5f, 0.5f }; // phản xạ

        glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
        glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
        glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
        glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0f); // Góc hình nón chiếu
        glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0f); // Độ tập trung ánh sáng

    }
    else {
        glDisable(GL_LIGHT1);
    }
}

void setupCustomSpotlight() {
    if (!isCustomSpotlightOn) {
        glDisable(GL_LIGHT2);
        return;
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT2);
    glEnable(GL_NORMALIZE);

    GLfloat lightPos[] = { spotlightPos[0], spotlightPos[1], spotlightPos[2], 1.0f };
    GLfloat spotDir[] = {
        spotlightTarget[0] - spotlightPos[0],
        spotlightTarget[1] - spotlightPos[1],
        spotlightTarget[2] - spotlightPos[2]
    };

    GLfloat diffuse[] = { 1.0f, 1.0f, 0.8f, 1.0f };
    GLfloat ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT2, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spotlightCutoff);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.0f);
}

void updateSpotlightPosition(GLfloat x, GLfloat y, GLfloat z) {
    spotlightPos[0] = x;
    spotlightPos[1] = y;
    spotlightPos[2] = z;
}

void updateSpotlightCutoff(GLfloat angle) {
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 90.0f) angle = 90.0f;
    spotlightCutoff = angle;
}

void setupAmbientLight() {
    if (!isAmbientLightOn) {
        glDisable(GL_LIGHT3);
        return;
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT3);
    glEnable(GL_NORMALIZE);

    // Vị trí ánh sáng vô hướng (w = 0): ánh sáng đến đều từ một hướng
    GLfloat lightPos[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // hướng ánh sáng

    // Ánh sáng dịu, tạo môi trường nền chung
    GLfloat ambient[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // ánh sáng môi trường
    GLfloat diffuse[] = { 0.2f, 0.2f, 0.2f, 1.0f };  // ánh sáng khuếch tán rất nhẹ
    GLfloat specular[] = { 0.1f, 0.1f, 0.1f, 1.0f }; // ánh sáng phản xạ nhẹ

    glLightfv(GL_LIGHT3, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT3, GL_SPECULAR, specular);
}


// Hàm đisplay 

void display() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Tính toán hướng nhìn từ góc xoay
    float centerX = camX + sin(angleY) * cos(angleX);
    float centerY = camY + sin(angleX);
    float centerZ = camZ - cos(angleY) * cos(angleX);

    gluLookAt(
        camX, camY, camZ,     // vị trí camera
        centerX, centerY, centerZ, // hướng nhìn tới
        0.0, 1.0, 0.0         // hướng lên
    );
    // thiet lap anh sáng
    setupCeilingLight(); 
    setupCeilingDir();
    setupCustomSpotlight();
    setupAmbientLight();

        
    // Vẽ cảnh
   // vexy();

    glPushMatrix();
    glScalef(2.0, 2.0, 2.0);
    drawRoom();
    drawCeilingBulb(0, 4.9, 0); // bong den

    glPopMatrix();

    glPushMatrix();
    glTranslated(1.2, 0, 0.8);
    glScaled(1.1, 1.1, 1.1);

    drawStudyTable(0, 0.2, -8.5); // ban hoc

    glPushMatrix();
    glScalef(0.8, 0.8, 0.8);
    glRotatef(180, 0, 1, 0);
    drawChairStudent(0, 0.2, 7.5); // ghe
    glPopMatrix();

    drawBookshelf(-5, 5, -9.3); // lich de ban
    drawDeskCalendar(1.5, 2.7, -8); // ke sach

    drawComputer(0, 2.65, -8.5); // máy tính 
   drawBookStack(-1.3, 3.2, -9); // sach
    drawLamp(1.5, 2.8, -9); // den hoc
    drawPenBox(-1.5, 3, -8); // hop but

    glPopMatrix();

    glPushMatrix();
    glScaled(1, 2.3, 2.45);
    drawBed(-4, 0.4, -3); // giuong ngu
    glPopMatrix();

    glPushMatrix();
    glScaled(1.5, 1.5, 1.5);
    drawWardrobe(90, 5.2, 2.0, -6); // vẽ tủ
    glPopMatrix();

    glPushMatrix();
    glScaled(3, 3, 3);

    drawPlantPot(2.9, 0.1, 2.9); // chậu cây 
    drawPlantPot(-2.9, 0.1, 2.9);
    glPopMatrix();

    drawAirConditioner(0, 7, -9.3); // dieu hoa
    
    glPushMatrix();
    glScaled(1.8, 1.8, 1.8);
    drawWindow(-90, 5.45, 2.5, 0); // cua so
    glPopMatrix();

    glPushMatrix();
    glScaled(2, 2.2, 1);
    drawDoor(4, 1.25, -9.5); // cua
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2.5, 0);
    glScaled(2.5, 1.5, 2.5);
    drawFan(0, 3, -2, 0); // quat tran 
    glPopMatrix();
   

    glPushMatrix();
    glScaled(2, 2, 2);
    drawPicture(0, 2.5, -4.85); // tranh
    glPopMatrix();

    glPushMatrix();
    glScaled(3, 1, 3);
    drawCarpet(0, 0.3, 0); // thảm 
    glPopMatrix();

    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, (float)w / h, 1.0, 100.0);
}

void normalKeys(unsigned char key, int x, int y) {
    float dx = sin(angleY);
    float dz = -cos(angleY);

    switch (key) {
    case 'w':
    case 'W':
        camX += dx * moveSpeed;
        camZ += dz * moveSpeed;
        break;
    case 's':
    case 'S':
        camX -= dx * moveSpeed;
        camZ -= dz * moveSpeed;
        break;
    case 'a':
    case 'A':
        camX += dz * moveSpeed;
        camZ -= dx * moveSpeed;
        break;
    case 'd':
    case 'D':
        camX -= dz * moveSpeed;
        camZ += dx * moveSpeed;
        break;
    case 'v':
    case 'V':
        camY += moveSpeed;
        break;
    case 'c':
    case 'C':
        camY -= moveSpeed;
        break;
        // Điều khiển ánh sáng
    case '1':
        isCeilingLightOn = true;
        break;
    case '2':
        isCeilingLightOn = false;
        break; 
    case '3':
        isLight_dir = true;
        break;
    case '4':
        isLight_dir = false;
        break;
    case '5': // Bật spotlight
        isCustomSpotlightOn = true;
        break;
    case '6': // Tắt spotlight
        isCustomSpotlightOn = false;
        break;
    case '7': // Dịch đèn sang phải (x tăng)
        spotlightPos[0] += 0.2f;
        break;
    case '8': // Dịch đèn sang trái (x giảm)
        spotlightPos[0] -= 0.2f;
        break;
    case '9': // Tăng góc chiếu
        updateSpotlightCutoff(spotlightCutoff + 5.0f);
        break;
    case '0': // Giảm góc chiếu
        updateSpotlightCutoff(spotlightCutoff - 5.0f);
        break;
    case '-':
        isAmbientLightOn = !isAmbientLightOn;
        break;
    }

    glutPostRedisplay(); // Vẽ lại cảnh
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_LEFT:
        angleY -= rotateSpeed; break;
    case GLUT_KEY_RIGHT:
        angleY += rotateSpeed; break;
    case GLUT_KEY_UP:
        angleX += rotateSpeed;
        if (angleX > 1.5f) angleX = 1.5f;
        break;
    case GLUT_KEY_DOWN:
        angleX -= rotateSpeed;
        if (angleX < -1.5f) angleX = -1.5f;
        break;
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_LIGHTING);               // Bật hệ thống ánh sáng
    glEnable(GL_COLOR_MATERIAL);         // Cho phép glColor ảnh hưởng tới vật liệu
    glEnable(GL_DEPTH_TEST);             // Bật kiểm tra độ sâu
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);             // Bật chế độ đổ bóng mịn
}

int main(int argc, char** argv) {
    // In hướng dẫn sử dụng
    printf("===== HUONG DAN SU DUNG PHIM =====\n");
    printf("== Dieu khien camera:\n");
    printf("  W/S: Tien/Lui\n");
    printf("  A/D: Trai/Phai\n");
    printf("  V/C: Len/Xuong\n");
    printf("  Mui ten trai/phai: Xoay huong nhin theo chieu ngang\n");
    printf("  Mui ten len/xuong: Xoay huong nhin theo chieu doc\n");
    printf("\n== Dieu khien den:\n");
    printf("  1/2: Bat/Tat den tran\n");
    printf("  3/4: Bat/Tat den dinh huong\n");
    printf("  5/6: Bat/Tat den spotlight\n");
    printf("  -  : Bat/Tat den ambient\n");
    printf("\n== Dieu chinh vi tri va goc chieu cua spotlight:\n");
    printf("  7/8: Dich den spotlight trai/phai\n");
    printf("  9/0: Tang/giam goc chieu cua spotlight\n");
    printf("==================================\n\n");

    // Khởi tạo cửa sổ OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Ve Goc Hoc Tap");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(normalKeys);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 0;
}
