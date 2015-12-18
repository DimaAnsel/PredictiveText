#include "widget.h"
#include "ui_widget.h"

// non-Qt includes //
#include "main.h"
#include "CharTree.h"
#include "functs.h"
#include "TreeEdit.h"
/////////////////////

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->tree = new CharTree();
    load(this->tree);
}

Widget::~Widget()
{
    save(this->tree);
    delete this->tree;
    delete ui;
}

void Widget::on_useWordButton_clicked()
{
    char tempStr[MAX_WORD_LEN];
    ui->enteredText->insertPlainText(ui->predictedWord->text()); // insert word
    strcpy(tempStr,ui->predictedWord->text().toUtf8().constData());
    this->tree->learnWord(tempStr); // learn word

    ui->wordEntry->setText(QString(""));
    ui->predictedWord->setText(QString(""));
}

void Widget::on_wordEntry_textEdited(const QString &arg1)
{
    int i;
    char wordEntryStr[MAX_WORD_LEN];
    char predictedWord[MAX_WORD_LEN];
    char tempStr[MAX_WORD_LEN] = {'\0'};

    strcpy(wordEntryStr,arg1.toUtf8().constData()); // convert to std::string
    // check for completed words
    for (i = (int)strlen(wordEntryStr); i >= 0; i--) {
        if (!trackedChar(wordEntryStr[i])) {
            strncpy(tempStr,wordEntryStr,i+1); // commit complete words
            strcpy(wordEntryStr,&wordEntryStr[i+1]); // remaining word (if any)
            ui->wordEntry->setText(QString(wordEntryStr));
            break; // exit loop
        }
    }
    if (strlen(tempStr)) {
        this->tree->learnWord(tempStr);
        ui->enteredText->insertPlainText(QString(tempStr));
    }

    this->tree->predictWord(wordEntryStr,predictedWord,MAX_WORD_LEN);

    ui->predictedWord->setText(QString(predictedWord));
}

void Widget::on_saveTreeButton_clicked()
{
    save(this->tree);
}

void Widget::on_reloadTreeButton_clicked()
{
    load(this->tree);
}

void Widget::on_clearTextButton_clicked()
{
    ui->enteredText->clear();
}

void Widget::on_saveTextButton_clicked()
{
    char tempStr[MAX_ENTEREDTEXT_LEN];
    FILE* fp;

    strcpy(tempStr,ui->enteredText->toPlainText().toUtf8().constData());
    fp = fopen(ENTEREDTEXT_FILENAME,"w");
    if (fp != nullptr) {
        fprintf(fp,tempStr);
        printf("Wrote to: %s\n",ENTEREDTEXT_FILENAME);
    }
    closeFile(fp);
}
