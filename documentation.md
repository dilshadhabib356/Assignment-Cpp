
### **Q1. Bit Rotation**

#### **Description**:
Rotate the binary representation of a number to the left or right by a specific number of steps.

#### **Usage**:
```cpp
BitRotator rotator;
rotator.rotate(<number>, <steps>, <direction>);
```
- `<number>`: Integer to be rotated.
- `<steps>`: Number of rotation steps.
- `<direction>`: `true` for right, `false` for left.

---

### **Q2. Add String Numbers**

#### **Description**:
Add two string numbers. If any non-numeric characters are present, return "-1".

#### **Usage**:
```cpp
StringAdder adder;
adder.add(<string_num1>, <string_num2>);
```
- `<string_num1>` & `<string_num2>`: Strings representing numbers.

---

### **Q3. Array Division**

#### **Description**:
Divide an array into chunks such that the sum of each chunk is <= `n`.

#### **Usage**:
```cpp
ArrayDivider divider;
divider.divide(<array>, <threshold>);
```
- `<array>`: Vector of integers.
- `<threshold>`: Sum threshold for chunks.

---

### **Q4. Password Strength Checker**

#### **Description**:
Check how many more characters are needed to make a strong password based on predefined criteria.

#### **Usage**:
```cpp
PasswordStrengthChecker checker;
checker.checkStrength(<password>);
```
- `<password>`: String representing the password.

---

### **Q5. RGB to HEX Converter**

#### **Description**:
Convert a color in RGB format to Hex format.

#### **Usage**:
```cpp
RGBConverter converter;
converter.toHex(<rgb_string>);
```
- `<rgb_string>`: String in format "rgb(r, g, b)".

---

### **Q6. Chatroom Application (Client & Server)**

#### **Description**:
Facilitates chatroom-style communication between multiple clients and a server.

#### **Client Usage**:
1. Initialize the client: `Client myClient;`
2. Connect to the server: `myClient.connect_to_server("server_IP", port);`
3. Keep the client running: `myClient.run();`

#### **Server Usage**:
1. Initialize the server: `Server myServer;`
2. Start the server: `myServer.start();`



------------------------------------------