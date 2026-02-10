# Hệ Thống Quản Lý Thư Viện - Tài Liệu Toàn Diện

## Mục Lục
1. [Giới Thiệu Dự Án](#giới-thiệu-dự-án)
2. [Design Patterns & Kiến Trúc](#design-patterns--kiến-trúc)
3. [Cấu Trúc Tệp và Thư Mục](#cấu-trúc-tệp-và-thư-mục)
4. [Các Thành Phần Chính](#các-thành-phần-chính)
5. [Chi Tiết Các Class](#chi-tiết-các-class)
6. [Cách Vận Hành Hệ Thống](#cách-vận-hành-hệ-thống)
7. [Xử Lý Lỗi](#xử-lý-lỗi)

---

## Giới Thiệu Dự Án

**Tên Dự Án**: Library Management System (Hệ Thống Quản Lý Thư Viện)

**Mục Đích**: Xây dựng một hệ thống quản lý thư viện toàn diện cho phép:
- Quản lý tài liệu (sách, tạp chí, video giáo dục)
- Quản lý người dùng (sinh viên, giảng viên)
- Xử lý mượn/trả tài liệu
- Tính toán tiền phạt trễ hạn
- Ghi nhận các giao dịch mượn

**Công Nghệ**: 
- Ngôn ngữ: C++11
- Tiêu chuẩn: C++11 (flag `-std=c++11`)
- Không sử dụng database, quản lý dữ liệu trong bộ nhớ

---

## Design Patterns & Kiến Trúc

### 1. **Singleton Pattern**
```
└── Library (Singleton)
    ├── Một instance duy nhất cho toàn bộ hệ thống
    ├── Truy cập qua: Library::getInstance()
    └── Quản lý tất cả tài liệu, người dùng, giao dịch
```

**Lợi ích**:
- Đảm bảo có duy nhất một instance của Library
- Kiểm soát truy cập từ khắp nơi trong chương trình
- Ngăn chặn Multiple Instantiation

**Chi tiết triển khai**:
```cpp
private:
    static Library* instance;              // Static instance
    Library();                              // Private constructor
    Library(const Library&) = delete;       // No copy constructor
    Library& operator=(const Library&) = delete;  // No copy assignment

public:
    static Library* getInstance() {
        if (instance == nullptr) {
            instance = new Library();
        }
        return instance;
    }
```

### 2. **Inheritance Hierarchy - Đa Hình**

#### **Cấu Trúc Tài Liệu**:
```
LibraryItem (Base Class - Abstract)
├── Book (Sách)
├── Magazine (Tạp chí)
└── EducationalVideo (Video Giáo Dục)
```

**Đặc điểm**:
- `LibraryItem` là lớp cơ sở, định nghĩa interface chung
- Các lớp con override các phương thức ảo thuần túy
- Mỗi loại tài liệu có cách tính tiền phạt khác nhau

#### **Cấu Trúc Người Dùng**:
```
User (Base Class)
├── StudentUser (Sinh viên)
│   └── Có suất mượn tối đa 5 cuốn
│   └── Chiết khấu tiền phạt 20%
│
└── FacultyUser (Giảng viên)
    └── Có suất mượn tối đa 10 cuốn
    └── Chiết khấu tiền phạt 50%
```

**Đặc điểm**:
- `User` định nghĩa các thuộc tính/phương thức cơ bản
- Các lớp con có quyền mượn, chiết khấu khác nhau
- Có thể mở rộng thêm loại người dùng mới

### 3. **Exception Handling - Xử Lý Lỗi**

```
std::exception
└── LibraryException (Base)
    ├── ItemNotFoundException
    ├── UserNotFoundException
    ├── ItemNotAvailableException
    ├── BorrowLimitExceededException
    ├── TransactionNotFoundException
    ├── InvalidTransactionException
    ├── InvalidDataException
    ├── DatabaseException
    ├── UnpaidFinesException
    └── DuplicateEntryException
```

**Mục đích**:
- Xử lý lỗi một cách có cấu trúc
- Cung cấp error code và thông báo chi tiết
- Dễ dàng catch và xử lý lỗi tuple

---

## Cấu Trúc Tệp và Thư Mục

```
LibraryManagement/
├── include/                    # Header files (.h)
│   ├── Library.h              # Quản lý chính
│   ├── LibraryItem.h          # Base class cho tài liệu
│   ├── Book.h, Magazine.h     # Loại tài liệu
│   ├── EducationalVideo.h
│   ├── User.h                 # Base class cho người dùng
│   ├── StudentUser.h          # Sinh viên
│   ├── FacultyUser.h          # Giảng viên
│   ├── Transaction.h          # Giao dịch mượn/trả
│   └── Exceptions.h           # Xử lý lỗi
│
├── src/                       # Implementation files (.cpp)
│   ├── Library.cpp
│   ├── LibraryItem.cpp
│   ├── Book.cpp, Magazine.cpp
│   ├── EducationalVideo.cpp
│   ├── User.cpp
│   ├── StudentUser.cpp
│   ├── FacultyUser.cpp
│   ├── Transaction.cpp
│   └── LibraryException.cpp
│
├── main.cpp                   # Chương trình chính
├── Makefile                   # File build
└── bin/library_system         # Executable (sau khi build)
```

---

## Các Thành Phần Chính

### 1. **Library** - Quản Lý Chính
- Singleton management quản lý tất cả dữ liệu
- Cung cấp API cho:
  - Quản lý tài liệu (thêm, tìm kiếm, xóa)
  - Quản lý người dùng (đăng ký, tìm kiếm)
  - Xử lý mượn/trả tài liệu
  - Tính toán tiền phạt

### 2. **LibraryItem Hierarchy** - Tài Liệu
Quản lý nhiều loại tài liệu khác nhau

### 3. **User Hierarchy** - Người Dùng
Quản lý nhiều loại người dùng với quyền khác nhau

### 4. **Transaction** - Giao Dịch
Ghi nhận các lần mượn/trả tài liệu

### 5. **Exception Handling** - Xử Lý Lỗi
Cung cấp mechanism xử lý lỗi đồng bộ

---

## Chi Tiết Các Class

### **1. LibraryItem (Base Class)**

#### **Mục Đích**:
Định nghĩa interface chung cho tất cả loại tài liệu

#### **Thuộc Tính**:
```cpp
protected:
    string itemId;              // ID duy nhất
    string title;               // Tên tài liệu
    string author;              // Tác giả
    int publicationYear;        // Năm xuất bản
    bool isAvailable;           // Có sẵn hay đang mượn
    double lateFeePerDay;       // Tiền phạt mỗi ngày trễ hạn
```

#### **Phương Thức Ảo Thuần Túy**:
```cpp
virtual void displayInfo() const = 0;                    // Hiển thị thông tin
virtual double calculateLateFee(int daysLate) const = 0; // Tính tiền phạt
virtual string getItemType() const = 0;                  // Lấy loại tài liệu
```

#### **Phương Thức Thông Thường**:
```cpp
bool checkAvailability() const;      // Kiểm tra có sẵn
void setAvailability(bool avail);    // Đặt trạng thái sẵn
```

---

### **2. Book (Sách)**

#### **Thuộc Tính**:
```cpp
private:
    string isbn;        // ISBN (International Standard Book Number)
    int numPages;       // Số trang
    string genre;       // Thể loại (Fiction, Science, History...)
    bool isHardcover;   // Bìa cứng hay mềm
```

#### **Cách Tính Tiền Phạt**:
```
- Sách bìa cứng: 2.0 đô/ngày
- Sách bìa mềm: 1.5 đô/ngày
```

#### **Ví Dụ**:
```cpp
Book book("B001", "The C++ Programming Language", 
          "Bjarne Stroustrup", 2013, 
          "978-0321563842", 1368, "Programming", true);
```

---

### **3. Magazine (Tạp Chí)**

#### **Thuộc Tính**:
```cpp
private:
    int issueNumber;    // Số phát hành
    string month;       // Tháng/mùa phát hành
    string publisher;   // Nhà xuất bản
```

#### **Cách Tính Tiền Phạt**:
```
- Cố định: 1.0 đô/ngày
```

#### **Ví Dụ**:
```cpp
Magazine mag("M001", "Nature", "Editor Team", 2024, 
             45, "March", "Nature Publishing Group");
```

---

### **4. EducationalVideo (Video Giáo Dục)**

#### **Thuộc Tính**:
```cpp
private:
    int durationMinutes;  // Thời lượng (phút)
    string resolution;    // Độ phân giải (1080p, 4K...)
    string subject;       // Môn học
    string language;      // Ngôn ngữ
```

#### **Cách Tính Tiền Phạt**:
```
- Phần trăm giá trị: 5% của (durationMinutes * 0.1) đô/ngày
- Ví dụ: Video 120 phút → 0.6 đô/ngày
```

#### **Ví Dụ**:
```cpp
EducationalVideo video("V001", "Advanced C++ Concepts", 
                       "Alex Allain", 2023,
                       480, "1080p", "Programming", "English");
```

---

### **5. User (Người Dùng - Base Class)**

#### **Thuộc Tính**:
```cpp
protected:
    string userId;                          // ID duy nhất
    string name;                            // Tên đầy đủ
    string email;                           // Email
    string phoneNumber;                     // Số điện thoại
    vector<Transaction*> borrowHistory;     // Lịch sử mượn
    int maxBorrowLimit;                     // Số tài liệu tối đa có thể mượn
    double totalFines;                      // Tổng tiền phạt
```

#### **Phương Thức Chính**:
```cpp
bool canBorrow() const;                 // Kiểm tra có thể mượn
void addTransaction(Transaction* trans); // Thêm giao dịch
void payFine(double amount);            // Chi trả tiền phạt

virtual int getCurrentBorrowCount() const;     // Số tài liệu đang mượn
virtual double getDiscountRate() const;        // % chiết khấu tiền phạt
```

#### **Mục Đích**:
- Định nghĩa cơ bản cho tất cả loại người dùng
- Cho phép mở rộng cho các loại người dùng khác

---

### **6. StudentUser (Sinh Viên)**

#### **Thuộc Tính Bổ Sung**:
```cpp
private:
    string studentId;    // MSSV
    string major;        // Ngành học (Computer Science, Math...)
    int yearOfStudy;     // Năm học (1, 2, 3, 4)
```

#### **Quyền Mượn**:
- **Suất mượn tối đa**: 5 tài liệu
- **Thời gian mượn**: 14 ngày (2 tuần)

#### **Chiết Khấu Tiền Phạt**:
- **20%** tiền phạt (0.8x bình thường)

#### **Phương Thức Đặc Biệt**:
```cpp
bool isGraduatingSoon() const;              // Sắp tốt nghiệp?
double calculateDiscountedFine(...) const;  // Tính tiền phạt có chiết khấu
void displayStudentStatus() const;          // Hiển thị trạng thái sinh viên
```

#### **Ví Dụ**:
```cpp
StudentUser student("U001", "Hoàng Văn A", 
                    "hoang.a@university.edu", "0912345678",
                    "20210001", "Computer Science", 3);
```

---

### **7. FacultyUser (Giảng Viên)**

#### **Thuộc Tính Bổ Sung**:
```cpp
private:
    string department;   // Bộ môn (Computer Science, Mathematics...)
    string position;     // Chức vị (Lecturer, Associate Professor...)
```

#### **Quyền Mượn**:
- **Suất mượn tối đa**: 10 tài liệu
- **Thời gian mượn**: 30 ngày (1 tháng)

#### **Chiết Khấu Tiền Phạt**:
- **50%** tiền phạt (0.5x bình thường)
- **Giảng viên cao cấp (Senior)**: Có thể yêu cầu mượn liên thư viện

#### **Phương Thức Đặc Biệt**:
```cpp
bool isSeniorFaculty() const;               // Là giảng viên cao cấp?
bool isEligibleForExtendedLoan() const;     // Có thể mượn dài hạn?
void displayFacultyStatus() const;          // Hiển thị trạng thái
void requestResearchMaterial(...) const;    // Yêu cầu tài liệu nghiên cứu
bool canRequestInterLibraryLoan() const;    // Có thể mượn liên thư viện?
```

#### **Ví Dụ**:
```cpp
FacultyUser faculty("U002", "TS. Nguyễn Văn B",
                    "nguyen.b@university.edu", "0987654321",
                    "Computer Science", "Associate Professor");
```

---

### **8. Transaction (Giao Dịch Mượn/Trả)**

#### **Mục Đích**:
Ghi nhận chi tiết mỗi lần mượn tài liệu

#### **Thuộc Tính**:
```cpp
private:
    string transactionId;    // ID giao dịch duy nhất
    User* borrower;          // Con trỏ đến người mượn
    LibraryItem* item;       // Con trỏ đến tài liệu
    time_t borrowDate;       // Thời điểm mượn
    time_t dueDate;          // Hạn trả
    time_t returnDate;       // Thời điểm trả (0 nếu chưa trả)
    double fineAmount;       // Tiền phạt nợ
```

#### **Vòng Đời Giao Dịch**:

```mermaid
┌──────────────────┐
│ borrowItem()     │  Tạo giao dịch
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│ Tài liệu đang    │  isAvailable = false
│ được mượn        │
└────────┬─────────┘
         │
         ▼ (Người dùng trả tài liệu)
┌──────────────────┐
│ processReturn()  │  Tính tiền phạt nếu trễ
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│ Giao dịch hoàn   │  returnDate được thiết lập
│ thành            │  isAvailable = true
└──────────────────┘
```

#### **Cách Tính Tiền Phạt**:
```
1. Nếu returnDate <= dueDate: 
   → Không phạt (fineAmount = 0)

2. Nếu returnDate > dueDate:
   → daysLate = (returnDate - dueDate) / 86400 (giây -> ngày)
   → fineAmount = item->calculateLateFee(daysLate)
   → Áp dụng chiết khấu nếu có: fineAmount *= (1 - discountRate)
```

#### **Phương Thức**:
```cpp
void processReturn();           // Xử lý trả tài liệu
bool isOverdue() const;         // Kiểm tra quá hạn?
double getFineAmount() const;   // Lấy tiền phạt
void displayDetailedInfo() const; // Hiển thị chi tiết
```

#### **Ví Dụ Use Case**:
```
1. Student U001 mượn Book B001 vào ngày 10/2/2026
   → Hạn trả: 24/2/2026 (14 ngày)
   → fineAmount = 0 (chưa trả)

2. Student trả vào ngày 28/2/2026 (4 ngày trễ)
   → daysLate = 4
   → Fine = 4 * 1.5 (bìa mềm) = 6.0 đô
   → Chiết khấu 20% = 6.0 * 0.8 = 4.8 đô
```

---

### **9. Library (Quản Lý Chính)**

#### **Singleton Pattern - Truy Cập Duy Nhất**:
```cpp
// Cách sử dụng:
Library* lib = Library::getInstance();  // Lấy instance

// Lần đầu: tạo mới
// Lần sau: trả về instance đã có
```

#### **Hàm Quản Lý Tài Liệu**:

**1. Thêm/Xóa Tài Liệu**:
```cpp
void addItem(LibraryItem* item);           // Thêm tài liệu
bool removeItem(string itemId);            // Xóa tài liệu
```

**2. Tìm Kiếm Tài Liệu**:
```cpp
LibraryItem* searchItemById(string id);              // Theo ID
vector<LibraryItem*> searchByTitle(string keyword); // Theo tiêu đề
vector<LibraryItem*> searchByAuthor(string author); // Theo tác giả
vector<LibraryItem*> searchByType(string type);     // Theo loại
vector<LibraryItem*> getAvailableItems() const;     // Tài liệu sẵn
```

**3. Hiển Thị**:
```cpp
void displayAllItems() const;  // Hiển thị tất cả (nhóm theo loại)
```

#### **Hàm Quản Lý Người Dùng**:

```cpp
void addUser(User* user);                    // Đăng ký người dùng
User* searchUserById(string id);             // Tìm theo ID
vector<User*> searchByName(string keyword); // Tìm theo tên
void displayAllUsers() const;                // Hiển thị tất cả
```

#### **Hàm Xử Lý Mượn/Trả**:

```cpp
Transaction* borrowItem(string userId, string itemId, int borrowDays);
// Thực hiện:
// 1. Tìm người dùng (throw UserNotFoundException nếu không tìm)
// 2. Tìm tài liệu (throw ItemNotFoundException nếu không tìm)
// 3. Kiểm tra tài liệu có sẵn (throw ItemNotAvailableException)
// 4. Kiểm tra quá giới hạn mượn (throw BorrowLimitExceededException)
// 5. Kiểm tra tiền phạt chưa trả (throw UnpaidFinesException)
// 6. Tạo giao dịch, cập nhật trạng thái tài liệu

Transaction* returnItem(string transactionId);
// Thực hiện:
// 1. Tìm giao dịch
// 2. Xử lý trả (processReturn)
// 3. Cập nhật trạng thái tài liệu (isAvailable = true)
// 4. Thêm tiền phạt vào tài khoản người dùng (nếu có)
```

#### **Ví Dụ Luồng Mượn Tài Liệu**:

```
┌─────────────────────────────────────┐
│ Library::borrowItem(userId, itemId) │
└─────────────────────────────────────┘
         │
         ▼ (Kiểm tra người dùng)
    ┌─────────┐
    │  Tìm    │  UserNotFoundException nếu không tìm
    │User?    │
    └────┬────┘
         │ (Kiểm tra tài liệu)
         ▼
    ┌─────────┐
    │ Tìm     │  ItemNotFoundException nếu không tìm
    │Item?    │
    └────┬────┘
         │ (Kiểm tra tài liệu có sẵn)
         ▼
    ┌─────────┐
    │Item có  │  ItemNotAvailableException nếu đang mượn
    │sẵn?     │
    └────┬────┘
         │ (Kiểm tra suất mượn)
         ▼
    ┌─────────┐
    │Chưa     │  BorrowLimitExceededException nếu vượt quá
    │vượt?    │
    └────┬────┘
         │ (Kiểm tra tiền phạt)
         ▼
    ┌─────────┐
    │Không có │  UnpaidFinesException nếu còn phạt
    │phạt     │
    └────┬────┘
         │
         ▼
    ┌──────────────────┐
    │ Tạo Transaction  │  - Set borrowDate, dueDate
    │ Cập nhật trạng   │  - item->setAvailability(false)
    │ thái tài liệu    │  - user->addTransaction(trans)
    └──────────────────┘
```

---

### **10. Exception Handling (Xử Lý Lỗi)**

#### **Base Class: LibraryException**

```cpp
class LibraryException : public std::exception {
protected:
    string message;     // Thông báo lỗi
    string errorCode;   // Mã lỗi (ITEM_NOT_FOUND, ...)

public:
    virtual const char* what() const noexcept;
    virtual string getErrorCode() const noexcept;
    virtual string getFormattedMessage() const noexcept;
};
```

#### **Các Exception Cụ Thể**:

| Exception | Error Code | Khi nào Xảy Ra |
|-----------|-----------|----------------|
| `ItemNotFoundException` | `ITEM_NOT_FOUND` | Tìm kiếm tài liệu không tìm thấy |
| `UserNotFoundException` | `USER_NOT_FOUND` | Tìm kiếm người dùng không tìm thấy |
| `ItemNotAvailableException` | `ITEM_NOT_AVAILABLE` | Tài liệu đang được mượn |
| `BorrowLimitExceededException` | `BORROW_LIMIT_EXCEEDED` | Vượt quá số tài liệu được phép mượn |
| `TransactionNotFoundException` | `TRANSACTION_NOT_FOUND` | Tìm kiếm giao dịch không tìm thấy |
| `InvalidDataException` | `INVALID_DATA` | Dữ liệu nhập vào không hợp lệ |
| `UnpaidFinesException` | `UNPAID_FINES` | Còn tiền phạt chưa trả |

#### **Ví Dụ Xử Lý**:

```cpp
try {
    Transaction* trans = library->borrowItem("U001", "B001", 14);
    cout << "Mượn thành công!" << endl;
    
} catch (UserNotFoundException& e) {
    cout << "Lỗi: " << e.what() << endl;
    cout << "Mã lỗi: " << e.getErrorCode() << endl;
    
} catch (ItemNotAvailableException& e) {
    cout << "Lỗi: " << e.getFormattedMessage() << endl;
    cout << "Tài liệu đang được mượn bởi: " 
         << e.getCurrentBorrower() << endl;
    
} catch (LibraryException& e) {  // Catch all library exceptions
    cout << "Lỗi thư viện: " << e.what() << endl;
}
```

---

## Cách Vận Hành Hệ Thống

### **1. Khởi Tạo Hệ Thống**

```cpp
int main() {
    // Lấy instance duy nhất
    Library* library = Library::getInstance();
    
    // Hệ thống sẵn sàng sử dụng
    return 0;
}
```

### **2. Thêm Tài Liệu**

```cpp
// Tạo tài liệu
Book* book1 = new Book(
    "B001",                          // itemId
    "The C++ Programming Language",  // title
    "Bjarne Stroustrup",            // author
    2013,                           // year
    "978-0321563842",               // isbn
    1368,                           // pages
    "Programming",                  // genre
    true                            // hardcover
);

// Thêm vào thư viện
library->addItem(book1);

// Tương tự với Magazine và EducationalVideo
Magazine* mag = new Magazine("M001", "Nature", "Editor", 2024, 
                             45, "March", "NPG");
library->addItem(mag);

EducationalVideo* video = new EducationalVideo("V001", "C++ Basics",
                         "Alex", 2023, 480, "1080p", "Programming", "EN");
library->addItem(video);
```

### **3. Đăng Ký Người Dùng**

```cpp
// Sinh viên
StudentUser* student = new StudentUser(
    "U001",                      // userId
    "Hoàng Văn A",              // name
    "hoang.a@univ.edu",         // email
    "0912345678",               // phone
    "20210001",                 // studentId
    "Computer Science",         // major
    3                           // year
);
library->addUser(student);

// Giảng viên
FacultyUser* faculty = new FacultyUser(
    "U002",
    "TS. Nguyễn Văn B",
    "nguyen.b@univ.edu",
    "0987654321",
    "Computer Science",
    "Associate Professor"
);
library->addUser(faculty);
```

### **4. Mượn Tài Liệu**

```cpp
try {
    // Sinh viên U001 mượn sách B001 (14 ngày)
    Transaction* trans = library->borrowItem("U001", "B001", 14);
    
    cout << "Mượn thành công!" << endl;
    trans->displayDetailedInfo();
    
} catch (BorrowLimitExceededException& e) {
    cout << "Đã mượn quá số lượng tối đa" << endl;
    cout << e.getFormattedMessage() << endl;
    
} catch (ItemNotAvailableException& e) {
    cout << "Tài liệu đang được mượn" << endl;
    
} catch (UserNotFoundException& e) {
    cout << "Không tìm thấy người dùng" << endl;
    
} catch (LibraryException& e) {
    cout << "Lỗi: " << e.what() << endl;
}
```

### **5. Trả Tài Liệu**

```cpp
try {
    // Trả tài liệu (transactionId: T001)
    Transaction* returned = library->returnItem("T001");
    
    if (returned->getFineAmount() > 0) {
        cout << "Phạt trễ hạn: $" << returned->getFineAmount() << endl;
    } else {
        cout << "Trả đúng hạn, không phạt" << endl;
    }
    
    returned->displayDetailedInfo();
    
} catch (TransactionNotFoundException& e) {
    cout << "Không tìm thấy giao dịch" << endl;
}
```

### **6. Thanh Toán Tiền Phạt**

```cpp
// Lấy người dùng
User* user = library->searchUserById("U001");

// Kiểm tra tiền phạt
cout << "Tiền phạt hiện tại: $" << user->getTotalFines() << endl;

// Thanh toán
user->payFine(5.0);
cout << "Sau thanh toán: $" << user->getTotalFines() << endl;
```

### **7. Tìm Kiếm**

```cpp
// Tìm theo ID
LibraryItem* item = library->searchItemById("B001");

// Tìm theo tiêu đề
vector<LibraryItem*> results = library->searchByTitle("C++");

// Tìm tài liệu sẵn có
vector<LibraryItem*> available = library->getAvailableItems();

// Tìm người dùng theo tên
vector<User*> users = library->searchByName("Hoàng");
```

### **8. Hiển Thị Thông Tin**

```cpp
// Hiển thị tất cả tài liệu (nhóm theo loại)
library->displayAllItems();

// Hiển thị tất cả người dùng
library->displayAllUsers();

// Hiển thị thông tin sinh viên
StudentUser* student = (StudentUser*)library->searchUserById("U001");
student->displayStudentStatus();

// Hiển thị thông tin giảng viên
FacultyUser* faculty = (FacultyUser*)library->searchUserById("U002");
faculty->displayFacultyStatus();
```

---

## Xử Lý Lỗi

### **Chi Tiết Từng Exception**

#### **1. ItemNotFoundException**
```cpp
// Khi xảy ra
LibraryItem* item = library->searchItemById("INVALID_ID");

// Xử lý
try {
    // ...
} catch (ItemNotFoundException& e) {
    cout << e.what() << endl;                    // "Item not found"
    cout << e.getErrorCode() << endl;            // "ITEM_NOT_FOUND"
    cout << e.getFormattedMessage() << endl;     // "[ITEM_NOT_FOUND] Item not found"
}
```

#### **2. BorrowLimitExceededException**
```cpp
// Khi xảy ra
// Sinh viên đã mượn 5 cuốn, cố gắng mượn thêm

// Xử lý
try {
    library->borrowItem("U001", "B006", 14);
} catch (BorrowLimitExceededException& e) {
    cout << e.what() << endl;
    // Output: "User has reached borrowing limit"
    cout << e.getCurrentCount() << "/" << e.getMaxLimit() << endl;
    // Output: "5/5"
}
```

#### **3. ItemNotAvailableException**
```cpp
// Khi xảy ra
// Tài liệu đang được mươn

// Xử lý
try {
    library->borrowItem("U001", "B001", 14);
} catch (ItemNotAvailableException& e) {
    cout << "Tài liệu: " << e.getItemId() << endl;
    cout << "Bị mượn bởi: " << e.getCurrentBorrower() << endl;
}
```

#### **4. UnpaidFinesException**
```cpp
// Khi xảy ra
// Người dùng còn tiền phạt chưa trả, muốn mượn tài liệu mới

// Xử lý
try {
    library->borrowItem("U001", "B002", 14);
} catch (UnpaidFinesException& e) {
    cout << "Còn tiền phạt chưa trả" << endl;
    cout << "Vui lòng thanh toán trước" << endl;
}
```

---

## Flow Chart - Luồng Hoạt Động Chính

### **Luồng Mượn Tài Liệu**

```
START
  │
  ├──► Kiểm tra người dùng tồn tại
  │    └──► UserNotFoundException
  │
  ├──► Kiểm tra tài liệu tồn tại
  │    └──► ItemNotFoundException
  │
  ├──► Kiểm tra tài liệu có sẵn
  │    └──► ItemNotAvailableException
  │
  ├──► Kiểm tra số lượng mượn
  │    └──► BorrowLimitExceededException
  │
  ├──► Kiểm tra tiền phạt
  │    └──► UnpaidFinesException
  │
  └──► Tạo Transaction
       - Set borrowDate, dueDate
       - item->setAvailability(false)
       - user->addTransaction(trans)
       └──► END (Success)
```

### **Luồng Trả Tài Liệu**

```
START
  │
  ├──► Tìm Transaction
  │    └──► TransactionNotFoundException
  │
  ├──► Gọi processReturn()
  │    └──► Tính tiền phạt nếu trễ
  │
  ├──► Cập nhật trạng thái tài liệu
  │    └──► item->setAvailability(true)
  │
  └──► Thêm tiền phạt vào tài khoản
       └──► END (Success)
```

---

## Ví Dụ Thực Tế Chi Tiết

### **Scenario: Một Tuần Hoạt Động Thư Viện**

```
[2026-02-09] Ngày 1 - Mở cửa
├── 09:00 Sinh viên Hoàng (U001) mượn "The C++ Book" (B001)
│   ├── Hạn trả: 2026-02-23 (14 ngày)
│   └── Không phạt
│
├── 10:00 Giảng viên Nguyễn (U002) mượn "Nature" (M001)
│   ├── Hạn trả: 2026-03-11 (30 ngày - FacultyUser)
│   └── Không phạt
│
└── 11:00 Video được thêm vào hệ thống

[2026-02-20] Ngày 8 - Hoàng trả sách sớm
├── Trả B001 (sớm 3 ngày)
├── Fine = 0 (không quá hạn)
└── displayDetailedInfo():
    ├── Borrow Date: 2026-02-09
    ├── Due Date: 2026-02-23
    ├── Return Date: 2026-02-20
    └── Fine Amount: $0.00

[2026-02-28] Ngày 19 - Hoàng mượn lại, nhưng quên trả
├── Mượn B001 lần 2 (2026-02-28)
├── Hạn trả: 2026-03-14
└── ...

[2026-03-20] Ngày 40 - Hoàng trả muộn
├── Transaction quá hạn 6 ngày
├── Fine tính:
│   ├── Day late = 6
│   ├── Book hard cover fee = 6 * 2.0 = $12.0
│   ├── Student discount 20% = 12.0 * 0.8 = $9.6
│   └── Fine Amount: $9.6
│
├── Cập nhật:
│   ├── user->totalFines += 9.6 ($9.6)
│   ├── Hoàng không thể mượn nếu không trả tiền
│
└── [2026-03-21] Hoàng thanh toán $9.6
    └── user->totalFines = 0
    └── Có thể mượn lại
```

---

## Tóm Tắt Kiến Trúc

```
┌─────────────────────────────────────────────────────────────┐
│                     LIBRARY SYSTEM                          │
│                    (Singleton Pattern)                      │
└───────────┬─────────────────────────────────────────────────┘
            │
    ┌───────┴───────┬──────────────┬──────────────┐
    │               │              │              │
    ▼               ▼              ▼              ▼
┌────────┐    ┌─────────┐    ┌────────┐    ┌──────────────┐
│  Items │    │  Users  │    │ Trans. │    │ Exceptions   │
└────────┘    └─────────┘    └────────┘    └──────────────┘
    │               │              │              │
    ├───┬──────┐    ├───┬──────┐  │            ├─ ItemNotFound
    │   │      │    │   │      │  │            ├─ UserNotFound
    ▼   ▼      ▼    ▼   ▼      ▼  ▼            ├─ ItemNotAvailable
  Book Mag Video Student Faculty Trans        ├─ BorrowLimitExceeded
                    │      │                   └─ ...
                    │      │
                  5 items 10 items
                  20% disc 50% disc
```

Hệ thống sử dụng **kế thừa nhiều cấp** để tổ chức code, **đa hình** để xử lý các loại tài liệu/người dùng khác nhau, và **exception handling** để xử lý lỗi một cách có cấu trúc.

---

## Kết Luận

Hệ thống Library Management được thiết kế theo các **design pattern chuyên nghiệp**:

1. **Singleton Pattern** cho Library
2. **Inheritance & Polymorphism** cho Items và Users
3. **Exception Handling** cho quản lý lỗi
4. **Separation of Concerns** với các class riêng biệt

Điều này làm cho code dễ dàng:
- ✅ Mở rộng (thêm loại người dùng/tài liệu mới)
- ✅ Maintain (thay đổi logic xử lý)
- ✅ Test (kiểm tra các thành phần độc lập)
- ✅ Debug (xác định lỗi nhanh chóng)
