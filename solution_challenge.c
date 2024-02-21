import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;

void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: FirstScreen(),
    );
  }
}

class FirstScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Healthcare Assistant'),
      ),
      body: SafeArea(
        child: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: <Widget>[
              Icon(
                Icons.favorite,
                size: 100.0,
                color: Colors.red,
              ),
              SizedBox(height: 20.0),
              Text(
                'Welcome!',
                style: TextStyle(fontSize: 24.0, fontWeight: FontWeight.bold),
              ),
              SizedBox(height: 10.0),
              ElevatedButton(
                onPressed: () {
                  Navigator.push(
                    context,
                    MaterialPageRoute(builder: (context) => LoginScreen()),
                  );
                },
                child: Text('Login'),
              ),
            ],
          ),
        ),
      ),
    );
  }
} //İlk ekran

class LoginScreen extends StatefulWidget {
  @override
  _LoginScreenState createState() => _LoginScreenState();
} //Giriş ekranı

class _LoginScreenState extends State<LoginScreen> {
  final TextEditingController idNumberController = TextEditingController();
  final TextEditingController passwordController = TextEditingController();
  bool showPassword = false;

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Login'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            Text(
              'Login Screen',
              style: TextStyle(fontSize: 24.0, fontWeight: FontWeight.bold),
            ),
            SizedBox(height: 20.0),
            // Kimlik numarası girişi
            TextFormField(
              controller: idNumberController,
              keyboardType: TextInputType.number,
              decoration: InputDecoration(
                labelText: 'Id Number',
                prefixIcon: Icon(Icons.credit_card),
                border: OutlineInputBorder(),
                focusedBorder: OutlineInputBorder(
                  borderSide: BorderSide(color: Colors.blue),
                ),
                enabledBorder: OutlineInputBorder(
                  borderSide: BorderSide(color: Colors.grey),
                ),
              ),
            ),
            SizedBox(height: 10.0),
            // Şifre girişi
            TextFormField(
              controller: passwordController,
              obscureText: !showPassword,
              decoration: InputDecoration(
                labelText: 'Password',
                prefixIcon: Icon(Icons.lock),
                suffixIcon: IconButton(
                  icon: Icon(
                    showPassword ? Icons.visibility : Icons.visibility_off,
                  ),
                  onPressed: () {
                    setState(() {
                      showPassword = !showPassword;
                    });
                  },
                ),
                border: OutlineInputBorder(),
                focusedBorder: OutlineInputBorder(
                  borderSide: BorderSide(color: Colors.blue),
                ),
                enabledBorder: OutlineInputBorder(
                  borderSide: BorderSide(color: Colors.grey),
                ),
              ),
            ),
            SizedBox(height: 20.0),
            ElevatedButton(
              onPressed: () {
                // Burada kimlik numarası ve şifre ile giriş işlemleri yapılabilir
                // Örnek olarak, bu bilgileri alarak ana sayfaya yönlendiriyoruz
                Navigator.pushReplacement(
                  context,
                  MaterialPageRoute(builder: (context) => HomeScreen()),
                );
              },
              child: Text('Login'),
            ),
          ],
        ),
      ),
    );
  }
}

class HomeScreen extends StatefulWidget {
  @override
  _HomeScreenState createState() => _HomeScreenState();
}

class _HomeScreenState extends State<HomeScreen> {
  List<HelpRequest> helpRequests = [];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Healthcare Asisstant'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: GridView.builder(
          gridDelegate: SliverGridDelegateWithFixedCrossAxisCount(
            crossAxisCount: 2,
            crossAxisSpacing: 16.0,
            mainAxisSpacing: 16.0,
          ),
          itemCount: 7, // Toplam balon sayısı (5 özellik + 1 yapay zeka yardımı)
          itemBuilder: (context, index) {
            if (index == 5) {
              // 6. Balon: Yapay Zeka Yardımı
              return _buildFeatureCard(
                icon: Icons.lightbulb_outline,
                title: 'AI Assistance',
                onTap: () {
                  _navigateToChatScreen(context);
                },
              );
            } if (index == 6) {
              // 7. Balon: Bir Gönül'e Dokun
              return _buildFeatureCard(
                icon: Icons.favorite,
                title: 'Touch a Heart',
                onTap: () {
                  // "Bir Gönül'e Dokun" baloncuk tıklandığında yapılacak işlemleri buraya ekleyin
                  _navigateToHelpSomeone(context);
                },
              );
            } else if (index == 4) {
              // 5. Balon: Canlı Yardım (Yardım Forumu)
              return _buildFeatureCard(
                icon: Icons.live_help,
                title: 'Live Help',
                onTap: () {
                  _navigateToLiveHelpScreen(context);
                },
              );
            } else {
              // Diğer balonlar
              return _buildFeatureCard(
                icon: _getIconForIndex(index),
                title: _getTitleForIndex(index),
                onTap: () {
                  if (index == 3) {
                    // 4. Balon: Acil Durum Hizmetleri
                    _navigateToEmergencyServiceScreen(context);
                  } else if (index == 0) {
                    // 1. Balon: İlaç Takibi
                    _navigateMedicationTrackingScreen(context);
                  } else {
                    // Diğer balonlara tıklanıldığında yapılacak işlemleri buraya ekleyebilirsiniz
                  }
                },
              );
            }
          },
        ),
      ),
    );
  }

  void _navigateToChatScreen(BuildContext context) {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => ChatScreen()),
    );
  }

  void _navigateToEmergencyServiceScreen(BuildContext context) {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => EmergencyServiceScreen()),
    );
  }

  void _navigateMedicationTrackingScreen(BuildContext context) {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => MedicationTrackingScreen()),
    );
  }

  void _navigateToHelpDetailsScreen(BuildContext context, HelpRequest request) {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => HelpDetailsScreen(request)),
    );
  }

  void _navigateToAddRequestScreen(BuildContext context) async {
    final result = await Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => AddRequestScreen()),
    );

    if (result != null && result is HelpRequest) {
      setState(() {
        helpRequests.add(result);
      });
    }
  }

  void _navigateToLiveHelpScreen(BuildContext context) {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => LiveHelpScreen()),
    );
  }

  void _navigateToHelpSomeone(BuildContext context) {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => HelpSomeoneScreen()),
    );
  }
}

IconData _getIconForIndex(int index) {
  switch (index) {
    case 0:
      return Icons.medical_services;
    case 1:
      return Icons.favorite;
    case 2:
      return Icons.event;
    case 3:
      return Icons.warning;
    case 4:
      return Icons.live_help;
    case 5:
      return Icons.help; // Varsayılan bir icon, değiştirebilirsiniz
    default:
      return Icons.help; // Varsayılan bir icon, değiştirebilirsiniz
  }
}

String _getTitleForIndex(int index) {
  switch (index) {
    case 0:
      return 'Medicine Tracking';
    case 1:
      return 'Health Tracking';
    case 2:
      return 'Making an Appointment';
    case 3:
      return 'Emergency Services';
    case 4:
      return 'Live Help';
    case 5:
      return 'AI Help';
    default:
      return 'Bilinmeyen';
  }
}

Widget _buildFeatureCard({
  required IconData icon,
  required String title,
  required VoidCallback onTap,
}) {
  return GestureDetector(
    onTap: onTap,
    child: Card(
      elevation: 5.0,
      shape: RoundedRectangleBorder(
        borderRadius: BorderRadius.circular(15.0),
      ),
      child: Padding(
        padding: EdgeInsets.all(8.0),
        child: Container(
          width: double.infinity,
          height: 150.0,
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            children: [
              Icon(
                icon,
                size: 50.0,
                color: Colors.blue,
              ),
              SizedBox(height: 8.0),
              Text(
                title,
                textAlign: TextAlign.center,
                style: TextStyle(
                  fontSize: 16.0,
                  fontWeight: FontWeight.bold,
                ),
              ),
            ],
          ),
        ),
      ),
    ),
  );
} //Ana sayfa


//ilaç takip
class Medication {
  final String name;
  final String dosage;
  final String frequency;

  Medication({
    required this.name,
    required this.dosage,
    required this.frequency,
  });
} //İlaç takip

class MedicationTrackingScreen extends StatefulWidget {
  @override
  _MedicationTrackingScreenState createState() => _MedicationTrackingScreenState();
}

class _MedicationTrackingScreenState extends State<MedicationTrackingScreen> {
  List<String> medications = [];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Medicine Tracking'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Text(
              'Medicines Followed:',
              style: TextStyle(fontSize: 20.0, fontWeight: FontWeight.bold),
            ),
            SizedBox(height: 10.0),
            _buildMedicationList(),
            SizedBox(height: 20.0),
            ElevatedButton(
              onPressed: () {
                _navigateToAddMedicationScreen(context);
              },
              child: Text('Add Medicine'),
            ),
          ],
        ),
      ),
    );
  }

  Widget _buildMedicationList() {
    return medications.isNotEmpty
        ? Column(
      crossAxisAlignment: CrossAxisAlignment.start,
      children: medications
          .map((medication) => Padding(
        padding: const EdgeInsets.symmetric(vertical: 8.0),
        child: Text(medication),
      ))
          .toList(),
    )
        : Text('There is no follow-up medicine yet.');
  }

  void _navigateToAddMedicationScreen(BuildContext context) async {
    // Navigator ile yeni bir sayfaya geçiş yapılır
    final result = await Navigator.push(
      context,
      MaterialPageRoute(
        builder: (context) => AddMedicationScreen(),
      ),
    );

    // Eğer kullanıcı geri butonuna basarak ekranı kapatmışsa ve bir sonuç dönmüşse,
    // bu sonuçtan ilaç bilgilerini alabiliriz
    if (result != null && result is MedicationInfo) {
      setState(() {
        medications.add('${result.medicationName} - ${result.dosage} - ${result.frequency}');
      });
    }
  }
}

class MedicationInfo {
  final String medicationName;
  final String dosage;
  final String frequency;

  MedicationInfo({required this.medicationName, required this.dosage, required this.frequency});
} // İlaç bilgilerini içerecek sınıf

class AddMedicationScreen extends StatefulWidget {
  @override
  _AddMedicationScreenState createState() => _AddMedicationScreenState();
}

class _AddMedicationScreenState extends State<AddMedicationScreen> {
  final TextEditingController medicationNameController = TextEditingController();
  final TextEditingController dosageController = TextEditingController();
  final TextEditingController frequencyController = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Add Medicine'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text(
              'Medicine Name:',
              style: TextStyle(fontSize: 18.0),
            ),
            TextField(
              controller: medicationNameController,
              decoration: InputDecoration(
                hintText: 'Enter the medicine name',
              ),
            ),
            SizedBox(height: 16.0),
            Text(
              'Dosage:',
              style: TextStyle(fontSize: 18.0),
            ),
            TextField(
              controller: dosageController,
              decoration: InputDecoration(
                hintText: 'Enter the medicine dosage',
              ),
            ),
            SizedBox(height: 16.0),
            Text(
              'Frequency:',
              style: TextStyle(fontSize: 18.0),
            ),
            TextField(
              controller: frequencyController,
              decoration: InputDecoration(
                hintText: 'Enter how many times a day you should take',
              ),
            ),
            SizedBox(height: 16.0),
            ElevatedButton(
              onPressed: () {
                // Kullanıcının girdiği bilgilerle bir şeyler yapabilirsiniz
                _saveMedicationDetailsAndPop();
              },
              child: Text('Add'),
            ),
          ],
        ),
      ),
    );
  }

  void _saveMedicationDetailsAndPop() {
    // İlaç bilgilerini içeren nesneyi oluştur
    final medicationInfo = MedicationInfo(
      medicationName: medicationNameController.text,
      dosage: dosageController.text,
      frequency: frequencyController.text,
    );

    // İlaç bilgilerini içeren nesneyi bir sonuç olarak geri döndür
    Navigator.pop(context, medicationInfo);
  }
}

class EmergencyServiceScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Emergency Services'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: <Widget>[
            Text(
              'Emergency Number in Turkey: 112',
              style: TextStyle(fontSize: 20.0, fontWeight: FontWeight.bold),
            ),
            SizedBox(height: 20.0),
            Text(
              'Health institutions near you:',
              style: TextStyle(fontSize: 16.0, fontWeight: FontWeight.bold),
            ),
            SizedBox(height: 10.0),
            _buildHealthInstitutions(),
          ],
        ),
      ),
    );
  }

  Widget _buildHealthInstitutions() {
    // Sağlık kuruluşları listesini burada göster
    return Text('Sample healthcare provider list');
  }
}


//Yapay zeka chati
class ChatScreen extends StatefulWidget {
  @override
  _ChatScreenState createState() => _ChatScreenState();
}

class _ChatScreenState extends State<ChatScreen> {
  final TextEditingController _messageController = TextEditingController();
  List<String> _chatMessages = [];

  // Sabit sorular ve cevapları
  Map<String, String> _faq = {
    'Hello?': 'Hi, How can I help you?',
    'What is your name?': 'I am Gemini AI!',
    'Adın ne?': 'Beni GPT-3.5 diye çağırabilirsin.',
    'Nereden geliyorsun?': 'OpenAI tarafından geliştirildim.',
    // ... diğer sorular ve cevapları ekleyin
  };

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('AI Chat'),
      ),
      body: Column(
        children: [
          Expanded(
            child: Container(
              padding: EdgeInsets.all(16.0),
              color: Colors.grey.shade200,
              child: ListView.builder(
                itemCount: _chatMessages.length,
                itemBuilder: (context, index) {
                  return _buildChatMessage(_chatMessages[index]);
                },
              ),
            ),
          ),
          _buildMessageInput(),
        ],
      ),
    );
  }

  Widget _buildChatMessage(String message) {
    return Align(
      alignment: Alignment.centerRight,
      child: Container(
        margin: EdgeInsets.symmetric(vertical: 8.0),
        padding: EdgeInsets.all(12.0),
        decoration: BoxDecoration(
          color: Colors.blue,
          borderRadius: BorderRadius.circular(10.0),
        ),
        child: Text(
          message,
          style: TextStyle(color: Colors.white),
        ),
      ),
    );
  }

  Widget _buildMessageInput() {
    return Container(
      color: Colors.white,
      padding: EdgeInsets.all(8.0),
      child: Row(
        children: [
          Expanded(
            child: TextField(
              controller: _messageController,
              decoration: InputDecoration(
                border: OutlineInputBorder(),
                hintText: 'Enter the messages...',
              ),
            ),
          ),
          SizedBox(width: 8.0),
          IconButton(
            icon: Icon(Icons.send),
            onPressed: () {
              _sendMessage(_messageController.text);
            },
          ),
        ],
      ),
    );
  }

  void _sendMessage(String message) async {
    if (message.isNotEmpty) {
      setState(() {
        _chatMessages.add(message);
      });

      // Yapay Zeka API'si ile iletişim kurma kısmı
      String aiResponse = await _getAIResponse(message);

      if (aiResponse.isNotEmpty) {
        setState(() {
          _chatMessages.add(aiResponse);
        });
      }

      // Mesaj gönderildikten sonra kutucuktaki mesajı temizle
      _messageController.clear();
    }
  }

  Future<String> _getAIResponse(String userMessage) async {
    // Kullanıcının mesajını kontrol et ve uygun cevabı döndür
    return _faq.containsKey(userMessage) ? _faq[userMessage]! : 'I don\'t understand.';
  }
}

  Future<String> _getAIResponse(String userMessage) async {
    // Gerçek bir API kullanmanız gerekiyor. Bu sadece örnek bir URL'dir.
    final apiUrl = Uri.parse('https://generativelanguage.googleapis.com/v1beta/models/gemini-1.0-pro:generateContent?key=AIzaSyAzrz8R0lHlG-Y6QHumlpy7TFF-ZMS2nRk');

    try {
      final response = await http.get(apiUrl);

      if (response.statusCode == 200) {
        Map<String, dynamic> responseData = json.decode(response.body);
        return 'AI: ${responseData['response']}';
      } else {
        return 'AI: No response received.';
      }
    } catch (e) {
      return 'AI: An error occurred.';
    }
  }


//Canlı Yardım Forum
class HelpRequest {
  final String name;
  final String contactInfo;
  final String helpType;
  final String location;
  final String category;
  bool isClosed;

  HelpRequest({
    required this.name,
    required this.contactInfo,
    required this.helpType,
    required this.location,
    required this.category,
    this.isClosed = false,
  });
}

class LiveHelpScreen extends StatefulWidget {
  @override
  _LiveHelpScreenState createState() => _LiveHelpScreenState();
}

class _LiveHelpScreenState extends State<LiveHelpScreen> {
  List<HelpRequest> helpRequests = [];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Live Help'),
      ),
      body: Column(
        children: [
          ElevatedButton(
            onPressed: () {
              _navigateToAddRequestScreen(context);
            },
            child: Text('Share a Help Request'),
          ),
          Expanded(
            child: ListView.builder(
              itemCount: helpRequests.length,
              itemBuilder: (context, index) {
                return _buildHelpRequestCard(helpRequests[index]);
              },
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildHelpRequestCard(HelpRequest request) {
    return Card(
      margin: EdgeInsets.all(8.0),
      child: ListTile(
        title: Text(request.helpType),
        subtitle: Text(request.location),
        trailing: request.isClosed
            ? Icon(Icons.check, color: Colors.green)
            : IconButton(
          icon: Icon(Icons.message),
          onPressed: () {
            _navigateToHelpDetailsScreen(context, request);
          },
        ),
      ),
    );
  }

  void _navigateToAddRequestScreen(BuildContext context) async {
    final result = await Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => AddRequestScreen()),
    );

    if (result != null && result is HelpRequest) {
      setState(() {
        helpRequests.add(result);
      });
    }
  }

  void _navigateToHelpDetailsScreen(BuildContext context, HelpRequest request) {
    Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => HelpDetailsScreen(request)),
    );
  }
}

class AddRequestScreen extends StatefulWidget {
  @override
  _AddRequestScreenState createState() => _AddRequestScreenState();
}

class _AddRequestScreenState extends State<AddRequestScreen> {
  final TextEditingController nameController = TextEditingController();
  final TextEditingController contactInfoController = TextEditingController();
  final TextEditingController helpTypeController = TextEditingController();
  final TextEditingController locationController = TextEditingController();
  final TextEditingController categoryController = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Share a Help Request'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            TextField(
              controller: nameController,
              decoration: InputDecoration(labelText: 'Name Surname'),
            ),
            TextField(
              controller: contactInfoController,
              decoration: InputDecoration(labelText: 'Contact information'),
            ),
            TextField(
              controller: helpTypeController,
              decoration: InputDecoration(labelText: 'Need for Help'),
            ),
            TextField(
              controller: locationController,
              decoration: InputDecoration(labelText: 'Location Information'),
            ),
            TextField(
              controller: categoryController,
              decoration: InputDecoration(labelText: 'Category Selection'),
            ),
            ElevatedButton(
              onPressed: () {
                _shareHelpRequest();
              },
              child: Text('Share a Help Request'),
            ),
          ],
        ),
      ),
    );
  }

  void _shareHelpRequest() {
    if (nameController.text.isNotEmpty &&
        contactInfoController.text.isNotEmpty &&
        helpTypeController.text.isNotEmpty &&
        locationController.text.isNotEmpty &&
        categoryController.text.isNotEmpty) {
      HelpRequest newRequest = HelpRequest(
        name: nameController.text,
        contactInfo: contactInfoController.text,
        helpType: helpTypeController.text,
        location: locationController.text,
        category: categoryController.text,
      );

      Navigator.pop(context, newRequest);
    } else {
      // Kullanıcıdan eksik bilgi isteyebilir veya bir hata mesajı gösterebilirsiniz.
    }
  }
}

class HelpDetailsScreen extends StatelessWidget {
  final HelpRequest helpRequest;

  HelpDetailsScreen(this.helpRequest);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Assistance Request Details'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Text('Name Surname: ${helpRequest.name}'),
            Text('Contact Information: ${helpRequest.contactInfo}'),
            Text('Need for Help: ${helpRequest.helpType}'),
            Text('Location Information: ${helpRequest.location}'),
            Text('Category: ${helpRequest.category}'),
            ElevatedButton(
              onPressed: () {
                // Yardım talebini kapatma işlemi burada yapılabilir.
              },
              child: Text('Yardım Talebini Kapat'),
            ),
          ],
        ),
      ),
    );
  }
}

class HelpSomeoneScreen extends StatefulWidget {
  @override
  _HelpSomeoneScreenState createState() => _HelpSomeoneScreenState();
}

class _HelpSomeoneScreenState extends State<HelpSomeoneScreen> {
  List<HelpItem> helpItems = [];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Touch a Heart'),
      ),
      body: Column(
        children: [
          ElevatedButton(
            onPressed: () {
              _navigateToAddHelpItemScreen(context);
            },
            child: Text('Add Help Request'),
          ),
          Expanded(
            child: ListView.builder(
              itemCount: helpItems.length,
              itemBuilder: (context, index) {
                return _buildHelpItem(
                  context,
                  helpItems[index].name,
                  helpItems[index].description,
                  helpItems[index].amount,
                );
              },
            ),
          ),
        ],
      ),
    );
  }

  void _navigateToAddHelpItemScreen(BuildContext context) async {
    final result = await Navigator.push(
      context,
      MaterialPageRoute(builder: (context) => AddHelpItemScreen()),
    );

    if (result != null && result is HelpItem) {
      setState(() {
        helpItems.add(result);
      });
    }
  }

  Widget _buildHelpItem(
      BuildContext context,
      String name,
      String description,
      String amount,
      ) {
    return Card(
      margin: EdgeInsets.all(8.0),
      child: ListTile(
        title: Text(name),
        subtitle: Text(description),
        trailing: Text(amount),
      ),
    );
  }
}

class HelpItem {
  final String name;
  final String description;
  final String amount;

  HelpItem({
    required this.name,
    required this.description,
    required this.amount,
  });
}

class AddHelpItemScreen extends StatefulWidget {
  @override
  _AddHelpItemScreenState createState() => _AddHelpItemScreenState();
}

class _AddHelpItemScreenState extends State<AddHelpItemScreen> {
  final TextEditingController nameController = TextEditingController();
  final TextEditingController descriptionController = TextEditingController();
  final TextEditingController amountController = TextEditingController();

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Add Help Request'),
      ),
      body: Padding(
        padding: EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            TextField(
              controller: nameController,
              decoration: InputDecoration(labelText: 'Name Surname'),
            ),
            TextField(
              controller: descriptionController,
              decoration: InputDecoration(labelText: 'Explanation'),
            ),
            TextField(
              controller: amountController,
              decoration: InputDecoration(labelText: 'Amount'),
            ),
            ElevatedButton(
              onPressed: () {
                _saveHelpItemAndPop(context);
              },
              child: Text('Add'),
            ),
          ],
        ),
      ),
    );
  }

  void _saveHelpItemAndPop(BuildContext context) {
    if (nameController.text.isNotEmpty &&
        descriptionController.text.isNotEmpty &&
        amountController.text.isNotEmpty) {
      HelpItem newHelpItem = HelpItem(
        name: nameController.text,
        description: descriptionController.text,
        amount: amountController.text,
      );

      Navigator.pop(context, newHelpItem);
    } else {
      // Kullanıcıdan eksik bilgi isteyebilir veya bir hata mesajı gösterebilirsiniz.
    }
  }
}
