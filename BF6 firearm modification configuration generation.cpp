#include <iostream> // 引入输入输出流库
#include <vector>   // 引入向量容器库
#include <string>   // 引入字符串库
#include <algorithm>// 引入算法库（如排序等）
#include <cstdlib> // 添加头文件以支持system函数
#define COLOR_DEFAULT       "\033[0m"
#define COLOR_Blue          "\033[0;34m"
#define COLOR_Green         "\033[0;32m"
#define COLOR_Red           "\033[0;31m"
#define COLOR_Yellow        "\033[0;33m"
#define COLOR_White         "\033[0;37m"
#define COLOR_Cyan          "\033[0;36m"
#define COLOR_Magenta       "\033[0;35m"

#define COLOR_BrightBlue    "\033[1;34m"
#define COLOR_BrightGreen   "\033[1;32m"
#define COLOR_BrightRed     "\033[1;31m"
#define COLOR_BrightYellow  "\033[1;33m"
#define COLOR_BrightWhite   "\033[1;37m"
#define COLOR_BrightCyan    "\033[1;36m"
#define COLOR_BrightMagenta "\033[1;35m"
using namespace std; // 使用标准命名空间
int Point;// 全局变量，保存当前点数限制
// 配件结构体，保存每个配件的参数和名称
struct Attachment {
    int point, hip, accuracy, control, mobility; // 点数、腰射、精准、控制、机动参数
    string name; // 配件名称
    Attachment() : point(0), hip(0), accuracy(0), control(0), mobility(0), name("") {} // 构造函数，参数初始化为0和空字符串
};

// 配置结果结构体，保存一组配件选择后的总参数和加权分
struct ResultConfig {
    int selected[10]; // 每部分选中的配件索引
    int totalPoint, hip, accuracy, control, mobility; // 总点数和各项参数
    double weightedScore; // 按权重计算后的总分
};

// 计算单个配件的加权分数
double calcScore(const Attachment& att, double hipW, double accW, double ctrlW, double mobW) {
    return att.hip * hipW / 100.0 + att.accuracy * accW / 100.0 +
        att.control * ctrlW / 100.0 + att.mobility * mobW / 100.0; // 按权重加权求和
}

// 优化选择函数，自动为枪械选择最佳配件组合
void M4A1(double hipWeight, double accuracyWeight, double controlWeight, double mobilityWeight) {
    int baseHip = 46, baseAccuracy = 27, baseControl = 36, baseMobility = 65; // 枪械基础参数
    Attachment parts[10][12]; // 所有部分的所有配件数组

    // TODO: 填充配件参数
    parts[0][0].name = "无"; // 第1部分第1号配件名称
    parts[0][0].point = 0;        // 点数
    parts[0][0].hip = 0;           // 腰射加成
    parts[0][0].accuracy = 0;      // 精准加成
    parts[0][0].control = 0;       // 控制加成
    parts[0][0].mobility = 0;      // 机动加成

    parts[0][1].name = "消焰器"; // 自己理解喵！
    parts[0][1].point = 10;        // 点数
    parts[0][1].hip = 0;           // 腰射加成
    parts[0][1].accuracy = 0;      // 精准加成
    parts[0][1].control = 0;       // 控制加成
    parts[0][1].mobility = 0;      // 机动加成
    
    parts[0][2].name = "标准消音器"; // 自己理解喵！
    parts[0][2].point = 20;        // 点数
    parts[0][2].hip = -6;           // 腰射加成
    parts[0][2].accuracy = 0;      // 精准加成
    parts[0][2].control = 0;       // 控制加成
    parts[0][2].mobility = 0;      // 机动加成

    parts[0][3].name = "线性补偿器"; // 自己理解喵！
    parts[0][3].point = 10;        // 点数
    parts[0][3].hip = 0;           // 腰射加成
    parts[0][3].accuracy = 3;      // 精准加成
    parts[0][3].control = -2;       // 控制加成
    parts[0][3].mobility = 0;      // 机动加成

    parts[0][4].name = "补偿制退器"; // 自己理解喵！
    parts[0][4].point = 20;        // 点数
    parts[0][4].hip = 0;           // 腰射加成
    parts[0][4].accuracy = 1;      // 精准加成
    parts[0][4].control = 3;       // 控制加成
    parts[0][4].mobility = 0;      // 机动加成

    parts[1][0].name = "14.5英寸卡宾枪型"; // 自己理解喵！
    parts[1][0].point = 15;        // 点数
    parts[1][0].hip = 0;           // 腰射加成
    parts[1][0].accuracy = 0;      // 精准加成
    parts[1][0].control = 0;       // 控制加成
    parts[1][0].mobility = 0;      // 机动加成
   
    parts[1][1].name = "11.5英寸突击队型"; // 自己理解喵！
    parts[1][1].point = 15;        // 点数
    parts[1][1].hip = 8;           // 腰射加成
    parts[1][1].accuracy = 0;      // 精准加成
    parts[1][1].control = 0;       // 控制加成
    parts[1][1].mobility = 0;      // 机动加成

    parts[1][2].name = "12.5英寸中型"; // 自己理解喵！
    parts[1][2].point = 10;        // 点数
    parts[1][2].hip = 0;           // 腰射加成
    parts[1][2].accuracy = 0;      // 精准加成
    parts[1][2].control = 0;       // 控制加成
    parts[1][2].mobility = 0;      // 机动加成

    parts[2][0].name = "无"; // 自己理解喵！
    parts[2][0].point = 0;        // 点数
    parts[2][0].hip = 0;           // 腰射加成
    parts[2][0].accuracy = 0;      // 精准加成
    parts[2][0].control = 0;       // 控制加成
    parts[2][0].mobility = 0;      // 机动加成

    parts[2][1].name = "6H64垂直握把"; // 自己理解喵！
    parts[2][1].point = 25;        // 点数
    parts[2][1].hip = 0;           // 腰射加成
    parts[2][1].accuracy = 4;      // 精准加成
    parts[2][1].control = 11;       // 控制加成
    parts[2][1].mobility = -6;      // 机动加成

    parts[2][2].name = "折叠垂直握把"; // 自己理解喵！
    parts[2][2].point = 10;        // 点数
    parts[2][2].hip = 0;           // 腰射加成
    parts[2][2].accuracy = 2;      // 精准加成
    parts[2][2].control = 5;       // 控制加成
    parts[2][2].mobility = 4;      // 机动加成

    parts[2][3].name = "条纹垂直握把"; // 自己理解喵！
    parts[2][3].point = 20;        // 点数
    parts[2][3].hip = 0;           // 腰射加成
    parts[2][3].accuracy = 3;      // 精准加成
    parts[2][3].control = 8;       // 控制加成
    parts[2][3].mobility = 4;      // 机动加成

    parts[3][0].name = "30发弹匣"; // 自己理解喵！
    parts[3][0].point = 5;        // 点数
    parts[3][0].hip = 0;           // 腰射加成
    parts[3][0].accuracy = 0;      // 精准加成
    parts[3][0].control = 0;       // 控制加成
    parts[3][0].mobility = 0;      // 机动加成

    parts[3][1].name = "36发弹匣"; // 自己理解喵！
    parts[3][1].point = 15;        // 点数
    parts[3][1].hip = 0;           // 腰射加成
    parts[3][1].accuracy = 0;      // 精准加成
    parts[3][1].control = 0;       // 控制加成
    parts[3][1].mobility = -4;      // 机动加成

    parts[3][2].name = "40发快速弹匣"; // 自己理解喵！
    parts[3][2].point = 30;        // 点数
    parts[3][2].hip = 0;           // 腰射加成
    parts[3][2].accuracy = 0;      // 精准加成
    parts[3][2].control = 0;       // 控制加成
    parts[3][2].mobility = -6;      // 机动加成

    parts[3][3].name = "20发快速弹匣"; // 自己理解喵！
    parts[3][3].point = 5;        // 点数
    parts[3][3].hip = 0;           // 腰射加成
    parts[3][3].accuracy = 0;      // 精准加成
    parts[3][3].control = 0;       // 控制加成
    parts[3][3].mobility = 12;      // 机动加成

    parts[4][0].name = "全金属被甲"; // 自己理解喵！
    parts[4][0].point = 5;        // 点数
    parts[4][0].hip = 0;           // 腰射加成
    parts[4][0].accuracy = 0;      // 精准加成
    parts[4][0].control = 0;       // 控制加成
    parts[4][0].mobility = 0;      // 机动加成

    parts[4][1].name = "钨芯"; // 自己理解喵！
    parts[4][1].point = 5;        // 点数
    parts[4][1].hip = 0;           // 腰射加成
    parts[4][1].accuracy = -1;      // 精准加成
    parts[4][1].control = -2;       // 控制加成
    parts[4][1].mobility = 0;      // 机动加成

    parts[4][2].name = "软尖"; // 自己理解喵！
    parts[4][2].point = 5;        // 点数
    parts[4][2].hip = 0;           // 腰射加成
    parts[4][2].accuracy = 0;      // 精准加成
    parts[4][2].control = 0;       // 控制加成
    parts[4][2].mobility = 0;      // 机动加成

    parts[5][0].name = "无"; // 自己理解喵！
    parts[5][0].point = 0;        // 点数
    parts[5][0].hip = 0;           // 腰射加成
    parts[5][0].accuracy = 0;      // 精准加成
    parts[5][0].control = 0;       // 控制加成
    parts[5][0].mobility = 0;      // 机动加成

    parts[5][0].name = "改进的弹匣卡榫"; // 自己理解喵！
    parts[5][0].point = 5;        // 点数
    parts[5][0].hip = 0;           // 腰射加成
    parts[5][0].accuracy = 0;      // 精准加成
    parts[5][0].control = 0;       // 控制加成
    parts[5][0].mobility = 0;      // 机动加成

    parts[5][0].name = "扩口的弹匣井"; // 自己理解喵！
    parts[5][0].point = 10;        // 点数
    parts[5][0].hip = 0;           // 腰射加成
    parts[5][0].accuracy = 0;      // 精准加成
    parts[5][0].control = 0;       // 控制加成
    parts[5][0].mobility = 0;      // 机动加成


    int selected[10] = { 0 }; // 记录每部分选中的配件索引，初始化为0
    int totalPoint = 0, hip = baseHip, accuracy = baseAccuracy, control = baseControl, mobility = baseMobility; // 初始化总点数和参数

    // 先选每部分性价比最高的配件
    for (int p = 0; p < 10; ++p) { // 遍历所有部分
        int bestIdx = 0; // 最优配件索引初始化为0
        double bestScore = calcScore(parts[p][0], hipWeight, accuracyWeight, controlWeight, mobilityWeight) / (parts[p][0].point + 1); // 计算第一个配件性价比
        for (int i = 1; i < 12; ++i) { // 遍历该部分的所有配件
            double score = calcScore(parts[p][i], hipWeight, accuracyWeight, controlWeight, mobilityWeight) / (parts[p][i].point + 1); // 计算当前配件性价比
            if (score > bestScore) { // 如果当前配件性价比更高
                bestScore = score;   // 更新最优性价比
                bestIdx = i;        // 更新最优配件索引
            }
        }
        selected[p] = bestIdx; // 记录该部分选中的配件
        totalPoint += parts[p][bestIdx].point; // 累加点数
        hip += parts[p][bestIdx].hip;          // 累加腰射
        accuracy += parts[p][bestIdx].accuracy;// 累加精准
        control += parts[p][bestIdx].control;  // 累加控制
        mobility += parts[p][bestIdx].mobility;// 累加机动
    }

    // 如果总点数超限，逐步替换性价比次高的配件
    while (totalPoint > Point) { // 当总点数超过100时
        int worstPart = -1;    // 记录需要替换的部分
        double worstDelta = 1e9; // 损失最小值初始化为极大值
        for (int p = 0; p < 10; ++p) { // 遍历所有部分
            int curIdx = selected[p]; // 当前选中的配件索引
            int nextIdx = curIdx;     // 次优配件索引初始化
            double curScore = calcScore(parts[p][curIdx], hipWeight, accuracyWeight, controlWeight, mobilityWeight) / (parts[p][curIdx].point + 1); // 当前配件性价比
            for (int i = 0; i < 12; ++i) { // 遍历该部分所有配件
                if (i == curIdx) continue; // 跳过当前已选配件
                double score = calcScore(parts[p][i], hipWeight, accuracyWeight, controlWeight, mobilityWeight) / (parts[p][i].point + 1); // 计算次优配件性价比
                double delta = curScore - score; // 损失值
                int pointDelta = parts[p][curIdx].point - parts[p][i].point; // 点数减少值
                if (pointDelta > 0 && delta < worstDelta) { // 如果点数减少且损失更小
                    worstDelta = delta; // 更新最小损失
                    worstPart = p;     // 记录需要替换的部分
                    nextIdx = i;      // 记录次优配件索引
                }
            }
            if (worstPart == p) selected[p] = nextIdx; // 替换为次优配件
        }
        // 重新计算总点数和参数
        totalPoint = 0; hip = baseHip; accuracy = baseAccuracy; control = baseControl; mobility = baseMobility; // 重置参数
        for (int p = 0; p < 10; ++p) { // 累加所有部分参数
            totalPoint += parts[p][selected[p]].point;
            hip += parts[p][selected[p]].hip;
            accuracy += parts[p][selected[p]].accuracy;
            control += parts[p][selected[p]].control;
            mobility += parts[p][selected[p]].mobility;
        }
        if (worstPart == -1) break; // 如果没有可替换的部分则跳出循环
    }

    // 输出结果
    double weightedScore = hip * hipWeight / 100.0 +
        accuracy * accuracyWeight / 100.0 +
        control * controlWeight / 100.0 +
        mobility * mobilityWeight / 100.0; // 计算加权总分
    printf(COLOR_Yellow "最佳配置如下喵！：\n" COLOR_DEFAULT);
    //cout << "最佳配置如下喵！：" << endl; // 输出提示
    for (int i = 0; i < 10; ++i) { // 输出每部分选中的配件信息
		//cout << i + 1; // 输出部分编号
        printf(COLOR_Green "第 " COLOR_DEFAULT);
        printf(COLOR_Yellow "%d" COLOR_DEFAULT, i+1);
        //cout << "第" << i + 1;
        printf(COLOR_Green "部分，选用配件编号， " COLOR_DEFAULT);
        printf(COLOR_Yellow "%d" COLOR_DEFAULT, selected[i]);
		//cout << selected[i]; // 输出选中的配件编号
        printf(COLOR_Green "配件名称：" COLOR_DEFAULT);
        printf(COLOR_Red "%s" COLOR_DEFAULT, parts[i][selected[i]].name.c_str());
        cout << endl;
    }
    printf(COLOR_Yellow "腰射：" COLOR_DEFAULT);
    printf(COLOR_Red "%d" COLOR_DEFAULT, hip);
    cout <<"（代表腰射能力）" << endl;         // 输出腰射参数
    printf(COLOR_Yellow "精准：" COLOR_DEFAULT);
    printf(COLOR_Red "%d" COLOR_DEFAULT, accuracy);
    cout << "（代表精准能力）" << endl;         // 输出腰射参数
    printf(COLOR_Yellow "控制：" COLOR_DEFAULT);
    printf(COLOR_Red "%d" COLOR_DEFAULT, control);
    cout << "（代表控制能力）" << endl;         // 输出腰射参数
    printf(COLOR_Yellow "机动：" COLOR_DEFAULT);
    printf(COLOR_Red "%d" COLOR_DEFAULT, mobility);
    cout << "（代表机动能力）" << endl;         // 输出腰射参数
    printf(COLOR_Yellow  "加权总分：" COLOR_DEFAULT);

    cout << weightedScore << "（代表综合评分）" << endl; // 输出加权总分
}










void Gun2(double hipWeight, double accuracyWeight, double controlWeight, double mobilityWeight) {
    int baseHip = 46, baseAccuracy = 27, baseControl = 36, baseMobility = 65; // 枪械基础参数
    Attachment parts[10][12]; // 所有部分的所有配件数组

    // TODO: 填充配件参数
    


    int selected[10] = { 0 }; // 记录每部分选中的配件索引，初始化为0
    int totalPoint = 0, hip = baseHip, accuracy = baseAccuracy, control = baseControl, mobility = baseMobility; // 初始化总点数和参数

    // 先选每部分性价比最高的配件
    for (int p = 0; p < 10; ++p) { // 遍历所有部分
        int bestIdx = 0; // 最优配件索引初始化为0
        double bestScore = calcScore(parts[p][0], hipWeight, accuracyWeight, controlWeight, mobilityWeight) / (parts[p][0].point + 1); // 计算第一个配件性价比
        for (int i = 1; i < 12; ++i) { // 遍历该部分的所有配件
            double score = calcScore(parts[p][i], hipWeight, accuracyWeight, controlWeight, mobilityWeight) / (parts[p][i].point + 1); // 计算当前配件性价比
            if (score > bestScore) { // 如果当前配件性价比更高
                bestScore = score;   // 更新最优性价比
                bestIdx = i;        // 更新最优配件索引
            }
        }
        selected[p] = bestIdx; // 记录该部分选中的配件
        totalPoint += parts[p][bestIdx].point; // 累加点数
        hip += parts[p][bestIdx].hip;          // 累加腰射
        accuracy += parts[p][bestIdx].accuracy;// 累加精准
        control += parts[p][bestIdx].control;  // 累加控制
        mobility += parts[p][bestIdx].mobility;// 累加机动
    }

    // 如果总点数超限，逐步替换性价比次高的配件
    while (totalPoint > Point) { // 当总点数超过100时
        int worstPart = -1;    // 记录需要替换的部分
        double worstDelta = 1e9; // 损失最小值初始化为极大值
        for (int p = 0; p < 10; ++p) { // 遍历所有部分
            int curIdx = selected[p]; // 当前选中的配件索引
            int nextIdx = curIdx;     // 次优配件索引初始化
            double curScore = calcScore(parts[p][curIdx], hipWeight, accuracyWeight, controlWeight, mobilityWeight) / (parts[p][curIdx].point + 1); // 当前配件性价比
            for (int i = 0; i < 12; ++i) { // 遍历该部分所有配件
                if (i == curIdx) continue; // 跳过当前已选配件
                double score = calcScore(parts[p][i], hipWeight, accuracyWeight, controlWeight, mobilityWeight) / (parts[p][i].point + 1); // 计算次优配件性价比
                double delta = curScore - score; // 损失值
                int pointDelta = parts[p][curIdx].point - parts[p][i].point; // 点数减少值
                if (pointDelta > 0 && delta < worstDelta) { // 如果点数减少且损失更小
                    worstDelta = delta; // 更新最小损失
                    worstPart = p;     // 记录需要替换的部分
                    nextIdx = i;      // 记录次优配件索引
                }
            }
            if (worstPart == p) selected[p] = nextIdx; // 替换为次优配件
        }
        // 重新计算总点数和参数
        totalPoint = 0; hip = baseHip; accuracy = baseAccuracy; control = baseControl; mobility = baseMobility; // 重置参数
        for (int p = 0; p < 10; ++p) { // 累加所有部分参数
            totalPoint += parts[p][selected[p]].point;
            hip += parts[p][selected[p]].hip;
            accuracy += parts[p][selected[p]].accuracy;
            control += parts[p][selected[p]].control;
            mobility += parts[p][selected[p]].mobility;
        }
        if (worstPart == -1) break; // 如果没有可替换的部分则跳出循环
    }

    // 输出结果
    double weightedScore = hip * hipWeight / 100.0 +
        accuracy * accuracyWeight / 100.0 +
        control * controlWeight / 100.0 +
        mobility * mobilityWeight / 100.0; // 计算加权总分
    printf(COLOR_Yellow "最佳配置如下喵！：\n" COLOR_DEFAULT);
    //cout << "最佳配置如下喵！：" << endl; // 输出提示
    for (int i = 0; i < 10; ++i) { // 输出每部分选中的配件信息
        //cout << i + 1; // 输出部分编号
        printf(COLOR_Green "第 " COLOR_DEFAULT);
        printf(COLOR_Yellow "%d" COLOR_DEFAULT, i + 1);
        //cout << "第" << i + 1;
        printf(COLOR_Green "部分，选用配件编号， " COLOR_DEFAULT);
        printf(COLOR_Yellow "%d" COLOR_DEFAULT, selected[i]);
        //cout << selected[i]; // 输出选中的配件编号
        printf(COLOR_Green "配件名称：" COLOR_DEFAULT);
        printf(COLOR_Red "%s" COLOR_DEFAULT, parts[i][selected[i]].name.c_str());
        cout << endl;
    }
    printf(COLOR_Yellow "腰射：" COLOR_DEFAULT);
    printf(COLOR_Red "%d" COLOR_DEFAULT, hip);
    cout << "（代表腰射能力）" << endl;         // 输出腰射参数
    printf(COLOR_Yellow "精准：" COLOR_DEFAULT);
    printf(COLOR_Red "%d" COLOR_DEFAULT, accuracy);
    cout << "（代表精准能力）" << endl;         // 输出腰射参数
    printf(COLOR_Yellow "控制：" COLOR_DEFAULT);
    printf(COLOR_Red "%d" COLOR_DEFAULT, control);
    cout << "（代表控制能力）" << endl;         // 输出腰射参数
    printf(COLOR_Yellow "机动：" COLOR_DEFAULT);
    printf(COLOR_Red "%d" COLOR_DEFAULT, mobility);
    cout << "（代表机动能力）" << endl;         // 输出腰射参数
    printf(COLOR_Yellow  "加权总分：" COLOR_DEFAULT);

    cout << weightedScore << "（代表综合评分）" << endl; // 输出加权总分
}












int main() {
    cout << COLOR_BrightBlue; // 枪械对应的编码
        cout << "M4A1 = 1   " << "********   " << "********   " << "********   " << "********   " << COLOR_Green"*号代表暂未上线的喵！" COLOR_BrightBlue << endl;;
        cout << "********   " << "********   " << "********   " << "********   " << "********   " << endl;
        cout << "********   " << "********   " << "********   " << "********   " << "********   " << endl;
        cout << "********   " << "********   " << "********   " << "********   " << "********   " << endl;
        cout << "********   " << "********   " << "********   " << "********   " << "********   " << endl;
        cout << "********   " << "********   " << "********   " << "********   " << "********   " << endl;
        cout << "********   " << "********   " << "********   " << "********   " << "********   " << endl;
        cout << "********   " << "********   " << "********   " << "********   " << "********   " << endl;
        cout << "********   " << "********   " << "********   " << "********   " << "********   " << endl;


    cout << COLOR_DEFAULT;
    while (true) { // 循环，支持重新配置
        printf(COLOR_Yellow "请选择枪械编号喵！（1 - 45）请看上方输出的表格喵！：\n " COLOR_DEFAULT);
        //cout << endl; // 提示输入枪械编号
        int gunIdx; // 枪械编号变量
        cin >> gunIdx; // 读取用户输入的枪械编号
        double hipWeight, accuracyWeight, controlWeight, mobilityWeight; // 权重变量
        printf(COLOR_Yellow "是否可以接受使用 " COLOR_DEFAULT);
        printf(COLOR_Red "机械瞄具 " COLOR_DEFAULT);
        printf(COLOR_Yellow "喵！ \n" COLOR_DEFAULT);
        //cout <<endl;
        printf(COLOR_Yellow "如果可以的喵请输入 " COLOR_DEFAULT);
        printf(COLOR_Red "1, " COLOR_DEFAULT);
        printf(COLOR_Yellow "反之的喵请输入 " COLOR_DEFAULT);
        printf(COLOR_Red "0\n " COLOR_DEFAULT);
        //cout << "如果可以的喵请输入1，反之的喵请输入0"<<endl;
        int choice2 = 5;
        cin >> choice2;//读取点数限制，0表示不可以使用机械瞄具，1表示可以使用机械瞄具
        if (choice2 == 0) {
            Point = 90;//自己理解喵！
        }
       // else {
       //     break;
       // }
        if (choice2 == 1) {
            Point = 100;//自己理解喵！
        }
        //else {
        //    break;
        //}
        if (choice2 != 0 && choice2 != 1) {
            printf(COLOR_Red "由于作者懒得写输入错误的循环，使用就直接停止程序了喵！请自行在此打开该程序开始生成配置喵！谢谢使用喵！ " COLOR_DEFAULT);//自己理解喵！
            //cout << "由于作者懒得写输入错误的循环，使用就直接停止程序了喵！请自行在此打开该程序开始生成配置喵！谢谢使用喵！";//自己理解喵！
            return 0;
        }
        cout << Point<<"//数字是用于测试使用的喵！不必在意喵！" << endl;
        // 权重输入与校验，确保总和不超过poin限制
        while (true) {
            printf(COLOR_Green "请输入腰射参数权重喵！（百分比）： " COLOR_DEFAULT);
            //cout << "请输入腰射参数权重（百分比）："; // 提示输入腰射权重
            cin >> hipWeight; // 读取腰射权重
            printf(COLOR_Green "请输入精准参数权重喵！（百分比）： " COLOR_DEFAULT);
            //cout << "请输入精准参数权重喵！喵！（百分比）："; // 提示输入精准权重
            cin >> accuracyWeight; // 读取精准权重
            printf(COLOR_Green "请输入控制参数权重喵！（百分比）： " COLOR_DEFAULT);
            //cout << "请输入控制参数权重喵！（百分比）："; // 提示输入控制权重
            cin >> controlWeight; // 读取控制权重
            printf(COLOR_Green "请输入机动参数权重喵！（百分比）： " COLOR_DEFAULT);
            //cout << "请输入机动参数权重喵！（百分比）："; // 提示输入机动权重
            cin >> mobilityWeight; // 读取机动权重

            double totalWeight = hipWeight + accuracyWeight + controlWeight + mobilityWeight; // 计算权重总和
            if (totalWeight > 100.0) { // 如果总和超过100
                printf(COLOR_Red "参数权重总和不能超过100%，请重新输入喵！\n " COLOR_DEFAULT);// 提示重新输入
                //cout << "参数权重总和不能超过100%，请重新输入喵！" << endl; 
            }
            else {
                break; // 合法则跳出循环
            }
        }

        switch (gunIdx) { // 根据枪械编号选择函数
        case 1: M4A1(hipWeight, accuracyWeight, controlWeight, mobilityWeight); break; // 调用1号枪械函数
        case 2: Gun2(hipWeight, accuracyWeight, controlWeight, mobilityWeight); break; // 调用2号枪械函数
        default: printf(COLOR_Red "枪械编号无效喵！\n " COLOR_DEFAULT); // 输入无效编号时提示
        }

        // 询问是否退出或重新配置
        printf(COLOR_Green "是否开始退出程序喵？输入 y 退出，输入其他任意键重新配置喵！：\n " COLOR_DEFAULT); // 提示用户选择
        string choice; // 用户选择变量
        cin >> choice; // 读取用户输入
        if (choice == "y" || choice == "Y") break; // 输入y或Y则退出循环
    }
    printf(COLOR_Magenta "要不要进作者b站主页给个关注喵！反正也不要钱的喵！可以的话 " COLOR_DEFAULT);
    printf(COLOR_Red "请输入“y”的喵！" COLOR_DEFAULT);
    printf(COLOR_Magenta "（哼，不行的话就随便按个按键吧，可不能是关机键什么的哦！记得按回车哦！）\n " COLOR_DEFAULT);
    string choiceup; // 用户选择变量
    cin >> choiceup; // 读取用户输入
    if (choiceup == "y" || choiceup == "Y") {
        system("start https://space.bilibili.com/1660344778?spm_id_from=333.788.0.0");//打开作者B站主页链接
        printf(COLOR_Magenta "谢谢使用喵！欢迎下次使用喵！\n " COLOR_DEFAULT);
    } else {
        printf(COLOR_Magenta "谢谢使用喵！欢迎下次使用喵！\n " COLOR_DEFAULT); // 输出感谢信息
    }
    return 0; // 程序结束
}