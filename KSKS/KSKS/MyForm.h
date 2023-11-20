#include <Winsock2.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <msclr/marshal_cppstd.h>
#pragma comment(lib, "ws2_32.lib")

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

struct Command {
    std::string name;
    std::vector<std::string> params;
};


bool invalid_command = false;
int paint = 0;

std::string commanda = "";
int int_param[6];
std::string string_param[3];
int paint2 = 0;


namespace KSKS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    /// <summary>
    /// Сводка для MyForm
    /// </summary>


    public ref class MyForm : public System::Windows::Forms::Form
    {
    private:
        UdpClient^ udpServer;
    private: System::Windows::Forms::Label^ label1;
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::Panel^ panel1;
           int port = 12345;
    private: System::Windows::Forms::Label^ label3;
    private: Bitmap^ drawingBitmap;
    public:
        MyForm(void)
        {
            InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //
            udpServer = gcnew UdpClient(port);
            udpServer->BeginReceive(gcnew AsyncCallback(this, &MyForm::ReceiveCallback), nullptr);
            drawingBitmap = gcnew Bitmap(panel1->Width, panel1->Height);
        }
    private:
        void ReceiveCallback(IAsyncResult^ ar)
        {
            IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Any, port);
            array<Byte>^ receiveBytes = udpServer->EndReceive(ar, endPoint);
            String^ receivedMessage = Encoding::ASCII->GetString(receiveBytes);

            // Обработка полученного сообщения
            // Ваш код для обработки сообщения
            this->Invoke(gcnew Action<String^>(this, &MyForm::parsi), receivedMessage);
            // Продолжаем прослушивать порт
            udpServer->BeginReceive(gcnew AsyncCallback(this, &MyForm::ReceiveCallback), nullptr);
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(27, 492);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(304, 27);
            this->label1->TabIndex = 0;
            this->label1->Text = L"";
            // 
            // panel1
            // 
            this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel1->Location = System::Drawing::Point(27, 26);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(720, 370);
            this->panel1->TabIndex = 2;
            this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(17, 421);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(368, 55);
            this->label3->TabIndex = 3;
            this->label3->Text = L"Обрана команда:";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(773, 592);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        void DrawRoundedRectangle(Graphics^ g, Pen^ pen, int x, int y, int width, int height, int radius)
        {
            GraphicsPath^ path = gcnew GraphicsPath();

            System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, y, width, height);

            int diameter = 2 * radius;
            System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, System::Drawing::Size(diameter, diameter));

            path->AddArc(arc, 180, 90);
            arc.X = rect.Right - diameter;
            path->AddArc(arc, 270, 90);
            arc.Y = rect.Bottom - diameter;
            path->AddArc(arc, 0, 90);
            arc.X = rect.Left;
            path->AddArc(arc, 90, 90);

            path->CloseFigure();


            g->DrawPath(pen, path);

            delete path;
        }

        void DrawRoundedRectangle2(Graphics^ g, int x, int y, int width, int height, int radius, Color fillColor)
        {
            // Создайте объект GraphicsPath
            System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();

            // Создайте прямоугольник
            System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, y, width, height);

            // Определите размеры закругления углов
            int diameter = 2 * radius;
            System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, System::Drawing::Size(diameter, diameter));

            // Добавьте дуги для закругленных углов
            path->AddArc(arc, 180, 90); // Верхний левый угол
            arc.X = rect.Right - diameter;
            path->AddArc(arc, 270, 90); // Верхний правый угол
            arc.Y = rect.Bottom - diameter;
            path->AddArc(arc, 0, 90);   // Нижний правый угол
            arc.X = rect.Left;
            path->AddArc(arc, 90, 90);  // Нижний левый угол

            // Замкнуть путь
            path->CloseFigure();

            // Заполнить прямоугольник заданным цветом
            SolidBrush^ fillBrush = gcnew SolidBrush(fillColor);
            g->FillPath(fillBrush, path);

            // Освободить ресурсы
            delete path;
            delete fillBrush;
        }

        void DrawText2(Graphics^ g, String^ text, Color textColor, int x, int y, int fonte, int len)
        {
            System::Drawing::Font^ font;
            switch (fonte)
            {
            case 1:
                font = gcnew System::Drawing::Font("Arial", len);
                break;
            case 2:
                font = gcnew System::Drawing::Font("Times New Roman", len);
                break;
            case 3:
                font = gcnew System::Drawing::Font("Courier New", len);
                break;
            case 4:
                font = gcnew System::Drawing::Font("Verdana", len);
                break;
            case 5:
                font = gcnew System::Drawing::Font("Tahoma", len);
                break;
            case 6:
                font = gcnew System::Drawing::Font("Comic Sans MS", len);
                break;
            default:
                invalid_command = true;
                break;
            }
            System::Drawing::Brush^ brush = gcnew SolidBrush(textColor);
            g->DrawString(text, font, brush, x, y);
        }

        Color MyCol(std::string mycol)
        {
            if ("red" == mycol)
            {
                return Color::Red;
            }
            else if ("blue" == mycol)
            {
                return Color::Blue;
            }
            else if ("black" == mycol)
            {
                return Color::Black;
            }
            else if ("brown" == mycol)
            {
                return Color::Brown;
            }
            else if ("green" == mycol)
            {
                return Color::Green;
            }
            else if ("white" == mycol)
            {
                return Color::White;
            }
            else if ("cyan" == mycol)
            {
                return Color::Cyan;
            }
            else if ("yellow" == mycol)
            {
                return Color::Yellow;
            }
            else  if ("magenta" == mycol)
            {
                return Color::Magenta;
            }
            else  if ("gray" == mycol)
            {
                return Color::Gray;
            }
            else if ("lightgray" == mycol)
            {
                return Color::LightGray;
            }
            else  if ("darkgray" == mycol)
            {
                return Color::DarkGray;
            }
            else if ("orange" == mycol)
            {
                return Color::Orange;
            }
            else if ("pink" == mycol)
            {
                return Color::Pink;
            }
            else if ("purple" == mycol)
            {
                return Color::Purple;
            }
            else {
                return Color::White;
                invalid_command = true;
            }
        }

        void drawImage(Graphics^ g, int x0, int y0, int w, int h, array<Color>^ imageData)
        {
            for (int x = 0; x < w; x++)
            {
                for (int y = 0; y < h; y++)
                {
                    Color pixelColor = imageData[x + y * w];
                    SolidBrush^ brush = gcnew SolidBrush(pixelColor);
                    g->FillRectangle(brush, x0 + x, y0 + y, 1, 1);
                }
            }
        }


        void parsi(String^ bufi_mes2)
        {
            std::string bufi_mes = msclr::interop::marshal_as<std::string>(bufi_mes2);
            ParseCommand(bufi_mes);
            label1->Text = bufi_mes2;

            if (invalid_command == false)
            {

                Color buf = MyCol(string_param[0]);

                Graphics^ g = Graphics::FromImage(drawingBitmap);
                Pen^ pen = gcnew Pen(buf, 2);
                SolidBrush^ brush = gcnew SolidBrush(buf);

                // Пример: рисование линии на основе параметров
                if (paint2 == 1)
                {
                    drawingBitmap = gcnew Bitmap(panel1->Width, panel1->Height);
                    panel1->BackColor = buf; // Замените 'buf' на желаемый цвет фона
                    panel1->Invalidate();
                }

                if (paint2 == 2) { // Режим "pixel"

                    int x1 = int_param[0];
                    int y1 = int_param[1];
                    g->DrawLine(pen, x1, y1, x1 + 1, y1 + 1);

                }
                if (paint2 == 3) { // Режим "draw line"

                    int x1 = int_param[0];
                    int y1 = int_param[1];
                    int x2 = int_param[2];
                    int y2 = int_param[3];

                    g->DrawLine(pen, x1, y1, x2, y2);
                }
                if (paint2 == 4) {

                    int x1 = int_param[0];
                    int y1 = int_param[1];
                    int x2 = int_param[2];
                    int y2 = int_param[3];

                    g->DrawRectangle(pen, x1, y1, x2, y2);
                }
                if (paint2 == 5) {

                    int x1 = int_param[0];
                    int y1 = int_param[1];
                    int x2 = int_param[2];
                    int y2 = int_param[3];

                    g->FillRectangle(brush, x1, y1, x2, y2);
                }
                if (paint2 == 6) {

                    int x1 = int_param[0];
                    int y1 = int_param[1];
                    int x2 = int_param[2];
                    int y2 = int_param[3];

                    g->DrawEllipse(pen, x1, y1, x2, y2);
                }
                if (paint2 == 7) {

                    int x1 = int_param[0];
                    int y1 = int_param[1];
                    int x2 = int_param[2];
                    int y2 = int_param[3];

                    g->FillEllipse(brush, x1, y1, x2, y2);
                }
                if (paint2 == 8)
                {
                    int x1 = int_param[0];
                    int y1 = int_param[1];
                    int x2 = int_param[2];

                    g->DrawEllipse(pen, x1, y1, x2, x2);
                }
                if (paint2 == 9)
                {
                    int x1 = int_param[0];
                    int y1 = int_param[1];
                    int x2 = int_param[2];

                    g->FillEllipse(brush, x1, y1, x2, x2);
                }
                if (paint2 == 10)
                {
                    int x = int_param[0];
                    int y = int_param[1];
                    int width = int_param[2];
                    int height = int_param[3];
                    int radius = int_param[4];

                    DrawRoundedRectangle(g, pen, x, y, width, height, radius);
                }
                if (paint2 == 11)
                {
                    int x = int_param[0];
                    int y = int_param[1];
                    int width = int_param[2];
                    int height = int_param[3];
                    int radius = int_param[4];

                    DrawRoundedRectangle2(g, x, y, width, height, radius, buf);
                }
                if (paint2 == 12)
                {
                    int x = int_param[0];
                    int y = int_param[1];
                    String^ textToDraw = msclr::interop::marshal_as<String^>(string_param[1]);
                    int font = int_param[2];
                    int len = int_param[3];

                    DrawText2(g, textToDraw, buf, x, y, font, len);
                }
                if (paint2 == 13)
                {
                    int x0 = int_param[0];
                    int y0 = int_param[1];
                    int width = int_param[2];
                    int height = int_param[3];
                    array<Color>^ imageData = gcnew array<Color>(width * height);

                    for (int i = 0; i < imageData->Length; i++)
                    {
                        imageData[i] = buf;
                    }


                    drawImage(g, x0, y0, width, height, imageData);
                }

                // Другие режимы рисования можно обработать аналогичным образом

                // Освободите ресурсы
                delete g;
                delete pen;
                delete brush;

                panel1->Invalidate();
                paint2 = 0;
            }
            else {
                label1->Text = "Ошибка! Неверная команда!";
                label2->Text = "Ошибка! Неверная команда!";
            }
        }


        Command ParseCommand(const std::string& commandStr) {
            Command command;

            int num_bif;

            std::istringstream s_stream(commandStr);
            std::string get_word;
            s_stream >> command.name;

            int j = 0;
            int i = 0;
            while (s_stream >> get_word) {
                if (get_word == ":")
                {
                    commanda = command.name + " : ";
                    break;
                }

                command.name += " " + get_word;
            }

            if (command.name == "clear display") {
                invalid_command = false;
                paint = 1;
                paint2 = 1;
            }
            else if (command.name == "draw pixel") {
                paint = 2;
                paint2 = 2;
                invalid_command = false;
            }
            else if (command.name == "draw line") {
                paint = 5;
                paint2 = 3;
                invalid_command = false;
            }
            else if (command.name == "draw rectangle")
            {
                paint = 10;
                paint2 = 4;
                invalid_command = false;
            }
            else if (command.name == "fill rectangle") {
                paint = 15;
                paint2 = 5;
                invalid_command = false;
            }
            else if (command.name == "draw ellipse") {
                paint = 20;
                paint2 = 6;
                invalid_command = false;
            }
            else if (command.name == "fill ellipse")
            {
                paint2 = 7;
                paint = 25;
                invalid_command = false;
            }
            else {
                invalid_command = true;
            }


            if (!invalid_command)
            {
                while (s_stream >> get_word) {
                    switch (paint)
                    {
                        //clear display
                        ///other
                    case 1: case 4: case 9: case 14: case 19: case 24: case 29:
                        command.params.push_back(get_word);
                        try {
                            num_bif = std::stoi(get_word);
                        }
                        catch (const std::invalid_argument& e) {
                            invalid_command = false;
                            string_param[j] = get_word;
                            j++;
                            if (paint != 52)
                            {
                                return command;
                            }
                            else {
                                paint++;
                            }
                        }
                        invalid_command = true;
                        break;

                    case 2: case 3: case 5: case 6: case 7: case 8: case 10: case 11: case 12: case 13:
                    case 15: case 16: case 17: case 18: case 20: case 21: case 22: case 23:
                    case 25: case 26: case 27: case 28:
                        command.params.push_back(get_word);
                        try {
                            num_bif = std::stoi(get_word);
                        }
                        catch (const std::invalid_argument& e) {
                            invalid_command = true;
                            return command;
                        }
                        invalid_command = false;
                        paint++;
                        int_param[i] = num_bif;
                        i++;
                        break;
                    }
                }
                invalid_command = true;
                return command;
            }
            else {
                return command;
            }
        }

        void mes_get(String^ message) {

        }
#pragma endregion
    private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        e->Graphics->DrawImage(drawingBitmap, 0, 0);
    }
    };
}
