#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

enum enOperationType { Plus = 1, Minnus = 2, Multiply = 3, Divide = 4, MixOP = 5 };
enum enGameLevel { Easy = 1, Mid = 2, Hard = 3, MixLevel = 4 };

string GetenOperationText(enOperationType OperationType) {
    string Text[5] = { "+", "-", "x", "/", "Mix" };
    return Text[OperationType - 1];
}

string GetGameLevelText(enGameLevel Level) {
    string Text[4] = { "Easy", "Mid", "Hard", "Mix" };
    return Text[Level - 1];
}

struct stQuestion {
    enOperationType OperationType;
    enGameLevel GameLevel;
    int Num1 = 0;
    int Num2 = 0;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool Istrue = false;
};

struct stQuizz {
    stQuestion QuestionList[100];
    enGameLevel GameLevel;
    enOperationType OpType;
    short NumberOfQuestions;
    int WrongAnswer = 0;
    int TrueAnswer = 0;
    bool IsPass = false;
};

int RandomNumber(int From, int To) {
    return rand() % (To + 1 - From) + From;
}

short ReadHowManyQuestion() {
    short QuestionCount;
    do {
        cout << "How many questions do you want to answer? (1-10): ";
        cin >> QuestionCount;
    } while (QuestionCount < 1 || QuestionCount > 10);
    return QuestionCount;
}

enGameLevel ReadQuestionLevel() {
    short Level;
    do {
        cout << "What is the level of questions [1] = Easy, [2] = Middle, [3] = Hard, [4] = Mix: ";
        cin >> Level;
    } while (Level < 1 || Level > 4);
    return (enGameLevel)Level;
}

enOperationType ReadOperationType() {
    short OperationType;
    do {
        cout << "Choose operation type: Plus = [1], Minus = [2], Multiply = [3], Divide = [4], Mix = [5]: ";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);
    return (enOperationType)OperationType;
}

enOperationType GetRandomOperatinType() {
    return (enOperationType)RandomNumber(1, 4);
}

int SimpleCalculator(int Number1, int Number2, enOperationType OPtype) {
    switch (OPtype) {
    case Plus:
        return Number1 + Number2;
    case Minnus:
        return Number1 - Number2;
    case Multiply:
        return Number1 * Number2;
    case Divide:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

stQuestion GenerateQuestion(enGameLevel Level, enOperationType OPtype) {
    stQuestion Question;
    if (Level == enGameLevel::MixLevel) {
        Level = (enGameLevel)RandomNumber(1, 3);
    }
    if (OPtype == enOperationType::MixOP) {
        OPtype = GetRandomOperatinType();
    }
    Question.OperationType = OPtype;

    switch (Level) {
    case enGameLevel::Easy:
        Question.Num1 = RandomNumber(1, 10);
        Question.Num2 = RandomNumber(1, 10);
        break;
    case enGameLevel::Mid:
        Question.Num1 = RandomNumber(10, 50);
        Question.Num2 = RandomNumber(10, 50);
        break;
    case enGameLevel::Hard:
        Question.Num1 = RandomNumber(50, 100);
        Question.Num2 = RandomNumber(50, 100);
        break;
    }

    if (Question.OperationType == Divide && Question.Num2 == 0) {
        Question.Num2 = 1;
    }

    Question.CorrectAnswer = SimpleCalculator(Question.Num1, Question.Num2, Question.OperationType);
    Question.GameLevel = Level;

    return Question;
}

void GenerateQuizQuestions(stQuizz& Quizz) {
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++) {
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.GameLevel, Quizz.OpType);
    }
}

int ReadPlayerAnswer() {
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber) {
    cout << endl;
    cout << "Question [" << QuestionNumber + 1 << "] of " << Quizz.NumberOfQuestions << endl;
    cout << Quizz.QuestionList[QuestionNumber].Num1 << " "
        << GetenOperationText(Quizz.QuestionList[QuestionNumber].OperationType) << " "
        << Quizz.QuestionList[QuestionNumber].Num2 << " = ?" << endl;
    cout << "\n---------" << endl;
}

void CorrectPlayerAnswer(stQuizz& Quizz, short QuestionNumber) {
    if (Quizz.QuestionList[QuestionNumber].CorrectAnswer != Quizz.QuestionList[QuestionNumber].PlayerAnswer) {
        Quizz.QuestionList[QuestionNumber].Istrue = false;
        Quizz.WrongAnswer++;
        cout << "Wrong Answer! The correct answer is: "
            << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else {
        Quizz.QuestionList[QuestionNumber].Istrue = true;
        Quizz.TrueAnswer++;
        cout << "Correct Answer!" << endl;
    }
}

void Check(stQuizz& Quizz) {
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
        CorrectPlayerAnswer(Quizz, QuestionNumber);
    }
    Quizz.IsPass = (Quizz.TrueAnswer >= Quizz.WrongAnswer);
}

string CheckStatus(bool Pass) {
    return Pass ? "Passed!" : "Failed!";
}

void PrintLastResults(stQuizz Quizz) {
    cout << endl;
    cout << "***** Game Over *****" << endl;
    cout << "Result: " << CheckStatus(Quizz.IsPass) << endl;
    cout << "Total Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Level: " << GetGameLevelText(Quizz.GameLevel) << endl;
    cout << "OperationType: " << GetenOperationText(Quizz.OpType) << endl;
    cout << "Correct Answers: " << Quizz.TrueAnswer << endl;
    cout << "Wrong Answers: " << Quizz.WrongAnswer << endl;

    
}

void PlayMathGame() {
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestion();
    Quizz.GameLevel = ReadQuestionLevel();
    Quizz.OpType = ReadOperationType();

    GenerateQuizQuestions(Quizz);
    Check(Quizz);
    PrintLastResults(Quizz);
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}

void StartGame() {
    char PlayAgain = 'y';
    do {
        ResetScreen();
        PlayMathGame();
        
        cout << "Do you want to play again? (Y/N): ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main() {
    srand((unsigned)time(0)); 
    StartGame();
    return 0;
}
