#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <string>
// 편의를 위해 namespace 사용
using namespace std;
// 데이터 구조체: 날짜와 금 가격
struct GoldData {
    int day;      // 시간의 흐름 (1일차, 2일차...)
    double price; // 금 가격 (달러)
};
// 통계적 예측 클래스 (Linear Regression)
class MarketPredictor {
private:
    vector<GoldData> history; // 과거 데이터 저장소
public:
    // 데이터 추가 메서드
    void addData(int day, double price) {
        history.push_back({ day, price });
    }
    // 예측 로직: 선형 회귀 (y = mx + b)
    // m: 기울기 (Slope), b: 절편 (Intercept)
    double predictNextPrice() {
        if (history.empty()) return 0.0;
        double n = history.size();
        double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_xx = 0.0;
        // 데이터 순회하며 통계량 계산
        for (const auto& data : history) {
            sum_x += data.day;
            sum_y += data.price;
            sum_xy += (data.day * data.price);
            sum_xx += (data.day * data.day);
        }
        // 기울기(m)와 절편(b) 계산 공식
        double m = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x);
        double b = (sum_y - m * sum_x) / n;
        // 다음 날짜 (마지막 날짜 + 1)
        double next_day = history.back().day + 1;
        // 예측값 반환: y = mx + b
        return m * next_day + b;
    }
    // 현재 추세 출력
    void printTrend() {
        if (history.size() < 2) {
            cout << "데이터가 부족하여 추세를 분석할 수 없습니다." << endl;
            return;
        }
        double prediction = predictNextPrice();
        double current = history.back().price;
        cout << "\n----------------------------------------" << endl;
        cout << " [분석 결과 Report]" << endl;
        cout << "----------------------------------------" << endl;
        cout << " 현재 금 시세: $" << current << endl;
        cout << " 내일 예측가: $" << prediction << endl;
        // 상승/하락 판단
        if (prediction > current) {
            cout << " ==> [상승] 추세입니다. (매수 고려)" << endl;
        }
        else {
            cout << " ==> [하락] 추세입니다. (매도/관망)" << endl;
        }
        cout << "----------------------------------------" << endl;
    }
};


int main() {
    // 프로그램 시작 데모
    cout << "=== C++ Gold Price Prediction System ===" << endl;
    MarketPredictor goldBot;
    // 1. 학습 데이터 입력 (가상의 최근 5일 금 시세)
    // 실제로는 API나 CSV 파일에서 읽어와야 함
    // 예: 1일차 $2000 -> 5일차 $2040 (상승 추세)
    goldBot.addData(1, 2000.50);
    goldBot.addData(2, 2010.20);
    goldBot.addData(3, 2005.80); // 살짝 떨어짐 이라는 설정
    goldBot.addData(4, 2025.10);
    goldBot.addData(5, 2040.00);
    // 2. 예측 실행
    goldBot.printTrend();
    return 0;
}