#pragma once
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <random>

namespace StudentManagementSplayTree {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            // Load data from Json;
            LoadDataFromJson();
        }
#pragma region StudentInfo Class
        ref class StudentInfo
        {
        public:
            int StudentId;
            String^ Name;
            String^ Course;
            int Year;

            StudentInfo(int id, String^ desc, String^ course, int year)
            {
                StudentId = id;
                Name = desc;
                Course = course;
                Year = year;
            }
        };

        ref class SplayNode {
        public:
            StudentInfo^ Info;
            SplayNode^ Left;
            SplayNode^ Right;

            SplayNode(StudentInfo^ info) {
                Info = info;
                Left = nullptr;
                Right = nullptr;
            }
        };

        ref class StudentSplayTree {
        public:
            SplayNode^ Root;

            StudentSplayTree() { Root = nullptr; }

            // splay operation
            SplayNode^ Splay(SplayNode^ root, int id) {
                if (root == nullptr || root->Info->StudentId == id)
                    return root;

                // if id at left
                if (id < root->Info->StudentId) {
                    if (root->Left == nullptr) return root;

                    // Zig-Zig (Left Left) left subtree of the left child
                    if (id < root->Left->Info->StudentId) {
                        root->Left->Left = Splay(root->Left->Left, id);
                        root = RotateRight(root);
                    }
                    // Zig-Zag (Left Right) right subtree of the left child
                    else if (id > root->Left->Info->StudentId) {
                        root->Left->Right = Splay(root->Left->Right, id);
                        if (root->Left->Right != nullptr)
                            root->Left = RotateLeft(root->Left);
                    }

                    return (root->Left == nullptr) ? root : RotateRight(root);
                }
                else {
                    // id at right
                    if (root->Right == nullptr) return root;

                    // Zag-Zig (Right Left) left subtree of the right child
                    if (id < root->Right->Info->StudentId) {
                        root->Right->Left = Splay(root->Right->Left, id);
                        if (root->Right->Left != nullptr)
                            root->Right = RotateRight(root->Right);
                    }
                    // Zag-Zag (Right Right) right subtree of the right child
                    else if (id > root->Right->Info->StudentId) {
                        root->Right->Right = Splay(root->Right->Right, id);
                        root = RotateLeft(root);
                    }

                    return (root->Right == nullptr) ? root : RotateLeft(root);
                }
            }

            // rotate right
            SplayNode^ RotateRight(SplayNode^ node) {
                SplayNode^ temp = node->Left;
                node->Left = temp->Right;
                temp->Right = node;
                return temp;
            }

            // rotate left
            SplayNode^ RotateLeft(SplayNode^ node) {
                SplayNode^ temp = node->Right;
                node->Right = temp->Left;
                temp->Left = node;
                return temp;
            }

            // insert a new node
            void Insert(StudentInfo^ Info) {
                if (Root == nullptr) {
                    Root = gcnew SplayNode(Info);
                    return;
                }

                Root = Splay(Root, Info->StudentId);

                if (Root->Info->StudentId == Info->StudentId)
                    return; // Info already exists

                SplayNode^ newNode = gcnew SplayNode(Info);

                if (Info->StudentId < Root->Info->StudentId) {
                    newNode->Right = Root;
                    newNode->Left = Root->Left;
                    Root->Left = nullptr;
                }
                else {
                    newNode->Left = Root;
                    newNode->Right = Root->Right;
                    Root->Right = nullptr;
                }

                Root = newNode;
            }

            // Search for an Info and splay it to the root
            StudentInfo^ Search(int id) {
                Root = Splay(Root, id);
                if (Root != nullptr && Root->Info->StudentId == id)
                    return Root->Info;
                return nullptr;
            }

            // delete node
            void Delete(int id) {
                if (Root == nullptr) return;

                Root = Splay(Root, id);

                if (Root->Info->StudentId != id)
                    return; //id not found

                if (Root->Left == nullptr) {
                    Root = Root->Right;
                }
                else {
                    SplayNode^ temp = Root->Right;
                    Root = Root->Left;
                    Root = Splay(Root, id);
                    Root->Right = temp;
                }
            }

            // display in order
            void InOrderTraversal(SplayNode^ node, System::Collections::Generic::List<StudentInfo^>^% Infos) {
                if (node != nullptr) {
                    InOrderTraversal(node->Left, Infos);
                    Infos->Add(node->Info);
                    InOrderTraversal(node->Right, Infos);
                }
            }
        };

#pragma endregion

#pragma region End Initialized UI
    protected:
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Button^ searchAllButton;
        System::Windows::Forms::TextBox^ inputTextBox;
        System::Windows::Forms::DataGridView^ studentGridView;
        System::ComponentModel::Container^ components;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn4;
        System::Windows::Forms::DataGridViewButtonColumn^ Action;
        System::Windows::Forms::Label^ label1;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
        System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
        System::Windows::Forms::DataGridViewTextBoxColumn^ Year;
        System::Windows::Forms::DataGridViewButtonColumn^ Update;
        System::Windows::Forms::DataGridViewButtonColumn^ Delete;


        // Local inventory data (BST)
        StudentSplayTree^ studentSplayTree = gcnew StudentSplayTree();
#pragma endregion

#pragma region Windows Form Designer generated code
    public:
        void InitializeComponent(void)
        {
            this->searchAllButton = (gcnew System::Windows::Forms::Button());
            this->inputTextBox = (gcnew System::Windows::Forms::TextBox());
            this->studentGridView = (gcnew System::Windows::Forms::DataGridView());
            this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->Year = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
            this->Update = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
            this->Delete = (gcnew System::Windows::Forms::DataGridViewButtonColumn());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->studentGridView))->BeginInit();
            this->SuspendLayout();
            // 
            // searchAllButton
            // 
            this->searchAllButton->Location = System::Drawing::Point(20, 20);
            this->searchAllButton->Name = L"searchAllButton";
            this->searchAllButton->Size = System::Drawing::Size(100, 30);
            this->searchAllButton->TabIndex = 0;
            this->searchAllButton->Text = L"Search All";
            this->searchAllButton->UseVisualStyleBackColor = true;
            this->searchAllButton->Click += gcnew System::EventHandler(this, &MyForm::SearchAllButton_Click);
            // 
            // inputTextBox
            // 
            this->inputTextBox->Location = System::Drawing::Point(195, 26);
            this->inputTextBox->Name = L"inputTextBox";
            this->inputTextBox->Size = System::Drawing::Size(283, 20);
            this->inputTextBox->TabIndex = 1;
            // 
            // studentGridView
            // 
            this->studentGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->studentGridView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(6) {
            this->dataGridViewTextBoxColumn1,
            this->dataGridViewTextBoxColumn2, 
            this->dataGridViewTextBoxColumn3, 
            this->Year, 
            this->Update, 
            this->Delete
            });
            this->studentGridView->Location = System::Drawing::Point(20, 70);
            this->studentGridView->Name = L"studentGridView";
            this->studentGridView->Size = System::Drawing::Size(800, 500);
            this->studentGridView->TabIndex = 2;
            this->studentGridView->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MyForm::studentGridView_CellContentClick);
            // 
            // dataGridViewTextBoxColumn4
            // 
            this->dataGridViewTextBoxColumn4->HeaderText = L"Year";
            this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(126, 29);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(56, 13);
            this->label1->TabIndex = 3;
            this->label1->Text = L"Student Id";
            // 
            // dataGridViewTextBoxColumn1
            // 
            this->dataGridViewTextBoxColumn1->HeaderText = L"Student Id";
            this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
            this->dataGridViewTextBoxColumn1->ReadOnly = true;
            // 
            // dataGridViewTextBoxColumn2
            // 
            this->dataGridViewTextBoxColumn2->HeaderText = L"Student Name";
            this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
            // 
            // dataGridViewTextBoxColumn3
            // 
            this->dataGridViewTextBoxColumn3->HeaderText = L"Course";
            this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
            // 
            // Year
            // 
            this->Year->HeaderText = L"Year";
            this->Year->Name = L"Year";
            // 
            // Update
            // 
            this->Update->HeaderText = L"Update";
            this->Update->Name = L"Update";
            this->Update->Text = L"Update";
            this->Update->ToolTipText = L"Update";
            // 
            // Delete
            // 
            this->Delete->HeaderText = L"Delete";
            this->Delete->Name = L"Delete";
            this->Delete->Text = L"Delete";
            this->Delete->ToolTipText = L"Delete";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(857, 628);
            this->Controls->Add(this->label1);
            this->Controls->Add(this->searchAllButton);
            this->Controls->Add(this->inputTextBox);
            this->Controls->Add(this->studentGridView);
            this->Name = L"MyForm";
            this->Text = L"Student Management";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->studentGridView))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
#pragma region Load From Json
        // Load data from JSON file into BST
        void LoadDataFromJson()
        {
            std::ifstream file("student_data.json");
            if (!file.is_open())
            {
                MessageBox::Show("Unable to open JSON file.");
                return;
            }

            nlohmann::json jsonData;
            file >> jsonData;

            for (const auto& Info : jsonData)
            {
                int id = Info["studentId"];
                String^ name = gcnew String(Info["name"].get<std::string>().c_str());
                String^ course = gcnew String(Info["course"].get<std::string>().c_str());
                int year = Info["year"];

                StudentInfo^ newInfo = gcnew StudentInfo(id, name, course, year);
                studentSplayTree->Insert(newInfo);
                newInfo = nullptr;
            }
            //PopulateGridView();
            file.close();
        }

        // Populate DataGridView by traversing BST in order
        void PopulateGridView()
        {
            System::Collections::Generic::List<StudentInfo^>^ Infos = gcnew System::Collections::Generic::List<StudentInfo^>();
            System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();

            studentSplayTree->InOrderTraversal(studentSplayTree->Root, Infos);

            stopwatch->Stop();
            String^ elapsedTime = String::Format("Search All Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", (double)stopwatch->ElapsedTicks);

            this->studentGridView->Rows->Clear();
            for each (StudentInfo ^ Info in Infos)
            {
                this->studentGridView->Rows->Add(Info->StudentId, Info->Name, Info->Course, Info->Year);
            }
            MessageBox::Show("Inventory retrieved all successfully!\n" + elapsedTime);
        }
#pragma endregion

#pragma region CRUD
        // Handle "Search All" button click
        void SearchAllButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ searchText = inputTextBox->Text->Trim();

            if (!String::IsNullOrEmpty(searchText))
            {
                int searchId;
                if (Int32::TryParse(searchText, searchId))
                {
                    System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();
                    StudentInfo^ Info = studentSplayTree->Search(searchId);

                    stopwatch->Stop();
                    String^ elapsedTime = String::Format("Search Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", stopwatch->ElapsedTicks);

                    if (Info != nullptr)
                    {
                        // Display search result in the DataGridView
                        studentGridView->Rows->Clear();
                        studentGridView->Rows->Add(Info->StudentId, Info->Name, Info->Course, Info->Year);
                        MessageBox::Show("Student retrieved successfully!\n" + elapsedTime);

                    }
                    else
                    {
                        stopwatch->Stop();
                        MessageBox::Show("Info not found.");
                    }
                }
                else
                {
                    MessageBox::Show("Please enter a valid Student Id.");
                }
            }
            else {
                PopulateGridView();
            }
        }

        // Handle update and delete actions
        void studentGridView_CellContentClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
        {
            if (e->RowIndex >= 0)
            {
                switch (e->ColumnIndex)
                {
                case 4: // Update button column
                {
                    int StudentId = Convert::ToInt32(this->studentGridView->Rows[e->RowIndex]->Cells[0]->Value);
                    String^ name = this->studentGridView->Rows[e->RowIndex]->Cells[1]->Value->ToString();
                    String^ course = this->studentGridView->Rows[e->RowIndex]->Cells[2]->Value->ToString();
                    int year = Convert::ToInt32(this->studentGridView->Rows[e->RowIndex]->Cells[3]->Value);

                    // Update the Student
                    UpdateStudentData(StudentId, name, course, year);
                    break;
                }
                case 5: // Delete button column
                {
                    int StudentId = Convert::ToInt32(this->studentGridView->Rows[e->RowIndex]->Cells[0]->Value);
                    DeleteStudentData(StudentId);
                    break;
                }
                }
            }
        }

        // Update Student data in the BST
        void UpdateStudentData(int StudentId, String^ name, String^ course, int year)
        {
            // Check if StudentId is 0, in which case we perform an insert
            if (StudentId == 0)
            {
                // Random number generation
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> distrib(1000000, 9999999); // 7-digit range
                int randomNumber = distrib(gen); //rand no
                StudentId = randomNumber;

                StudentInfo^ newInfo = gcnew StudentInfo(StudentId, name, course, year);

                System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();
                // insert to splay tree
                studentSplayTree->Insert(newInfo);

                stopwatch->Stop();
                String^ elapsedTime = String::Format("Insert Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", stopwatch->ElapsedTicks);

                MessageBox::Show("New Student Info ( id: " + StudentId + ") inserted successfully!\n" + elapsedTime);
                PopulateGridView();
            }
            else {
                System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();

                StudentInfo^ Info = studentSplayTree->Search(StudentId);
                if (Info != nullptr)
                {

                    Info->Name = name;
                    Info->Course = course;
                    Info->Year = year;

                    stopwatch->Stop();
                    String^ elapsedTime = String::Format("Update Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", stopwatch->ElapsedTicks);

                    MessageBox::Show("Student (id: " + StudentId + ") updated successfully!\n" + elapsedTime);
                    PopulateGridView();
                }
                else
                {
                    stopwatch->Stop();
                    MessageBox::Show("Info not found for update.");
                }
            }
        }

        // Delete Student data from the BST
        void DeleteStudentData(int StudentId)
        {
            System::Diagnostics::Stopwatch^ stopwatch = System::Diagnostics::Stopwatch::StartNew();

            studentSplayTree->Delete(StudentId);

            stopwatch->Stop();
            String^ elapsedTime = String::Format("Delete Operation completed in {0} ticks (1 milliseconds = 1000 ticks).", stopwatch->ElapsedTicks);

            MessageBox::Show("Student (id: " + StudentId + ") deleted successfully!" + elapsedTime);
            PopulateGridView();
        }
#pragma endregion
    };
}
