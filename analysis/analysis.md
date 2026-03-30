Analysis Document - Design Pattern Pretest
PART A — Creational Pattern Analysis
A1 — Factory

Where are modifier objects created?
Objek modifier diciptakan di dalam file src/ModifierFactory.cpp, tepatnya di dalam fungsi statis ModifierFactory::createModifier(type, name, value).

Explain:

    Which class creates them: Class ModifierFactory.

    Why centralizing creation is beneficial: Pemusatan ini (sentralisasi) sangat menguntungkan karena memisahkan logika pembuatan objek dari penggunaan objek. Class seperti ShopSystem tidak perlu melakukan #include untuk setiap tipe modifier (seperti FlatBonus.h atau Multiplier.h). ShopSystem hanya perlu memanggil Factory dan meminta objek berdasarkan tipe string (misal: "Flat" atau "Mult"). Jika ada perubahan pada cara konstruksi modifier, kita hanya perlu mengubah kodenya di Factory tanpa menyentuh class lain.

A2 — Extensibility

Explain how you added SquareScoreModifier. Which files changed?
Untuk menambahkan SquareScoreModifier, saya membuat class baru yang mewarisi IModifier (membuat modifiers/SquareScoreModifier.h dan modifiers/SquareScoreModifier.cpp), lalu mengimplementasikan fungsi apply() untuk mengkuadratkan skor. Setelah itu, saya hanya perlu menambahkan satu kondisi else if (type == "Square") di dalam file src/ModifierFactory.cpp.

Was your design easy to extend?
Sangat mudah. Karena saya menggunakan prinsip Open/Closed Principle, saya bisa menambahkan fitur baru (modifier baru) tanpa harus mengubah kode inti di RunSession.cpp atau antarmuka ShopSystem.cpp. Sistem langsung mengenali modifier baru tersebut.
A3 — Factory Method (Conceptual)

If you had multiple shop types, how would Factory Method help? Provide example interface.
Jika ada beberapa jenis shop (misal: BasicShop dan RareShop), Factory Method memungkinkan kita mendefinisikan interface pembuatan objek, tapi membiarkan subclass menentukan class mana yang diinstansiasi.
Contoh Interface:
C++

class IShopFactory {
public:
    virtual IModifier* createRandomModifier() = 0;
};
// RareShopFactory meng-override fungsi ini untuk mereturn modifier dengan value yang lebih tinggi (multiplier x5).

A4 — Prototype (Conceptual)

Explain how Clone() could help duplicate modifiers. Where would Clone() be implemented?
Fungsi Clone() berguna jika game memiliki mekanik seperti kartu "Duplicate", di mana pemain bisa menyalin modifier yang sudah mereka miliki. Fungsi ini akan diimplementasikan sebagai virtual IModifier* clone() = 0; di dalam interface IModifier.h, dan setiap concrete class (seperti FlatBonus) akan mereturn instance baru dengan nilai variabel (bonus/multiplier) yang sama persis dengan objek aslinya.
A5 — Singleton (Conceptual)

Did you use global objects? Explain advantages and risks.
Saya tidak menggunakan Singleton (objek global) dalam implementasi ini; instansiasi dilakukan secara normal di RunSession.

    Advantages: Singleton berguna untuk sistem seperti AudioManager atau GameManager di mana kita hanya butuh satu akses terpusat di seluruh sistem.

    Risks: Singleton membuat coupling yang sangat kuat (kode saling terikat), status globalnya sulit dilacak jika terjadi bug, dan sangat menyulitkan Unit Testing.

PART B — Structural Pattern Analysis
B1 — Decorator Concept

Explain how your modifier system behaves like a Decorator pattern. What is being decorated?
Sistem modifier saya beroperasi layaknya sebuah pipeline yang membungkus (mendekorasi) nilai skor. Dalam fungsi RunSession::calculateScore(), skor dasar (integer) dilewatkan secara berurutan ke dalam fungsi apply() milik setiap objek IModifier di dalam vector activeModifiers.

    What is being decorated? Nilai "Base Score" adalah yang didekorasi/dimodifikasi. Setiap modifier menerima skor dari modifier sebelumnya, mengubahnya, dan meneruskannya (seperti roundScore = mod->apply(roundScore);).

B2 — Modifier Order

Does modifier order affect score? Explain example using your code.
Ya, urutan sangat memengaruhi hasil akhir. Urutan dieksekusi berdasarkan posisi modifier di dalam list activeModifiers (sesuai urutan pembelian).
Contoh: Jika Base Score = 100.

    Jika FlatBonus (+50) di urutan pertama dan Multiplier (x2) kedua: (100 + 50) * 2 = 300.

    Jika Multiplier (x2) di urutan pertama dan FlatBonus (+50) kedua: (100 * 2) + 50 = 250.

B3 — Composite (Conceptual)

Explain how a modifier group could be implemented.
Composite pattern bisa diimplementasikan dengan membuat class ModifierGroup yang mengimplementasikan antarmuka IModifier. ModifierGroup ini memiliki list/vector yang berisi pointer ke IModifier lainnya (bisa modifier tunggal atau grup lain). Saat fungsi apply() pada ModifierGroup dipanggil, ia akan melakukan iterasi dan memanggil apply() ke semua children di dalamnya.
B4 — Adapter (Conceptual)

Explain how you would integrate an external scoring system using Adapter.
Jika ada library eksternal (misal: LegacyScoreAPI) yang menerima input array biasa (int[]) alih-alih std::vector<Card>, saya akan membuat class AdapterScoringStrategy yang mengimplementasikan IScoringStrategy. Di dalam fungsi calculateBaseScore(vector<Card>), Adapter ini akan menerjemahkan vector kartu tersebut menjadi int[], lalu memanggil fungsi dari LegacyScoreAPI, dan mengembalikan hasilnya ke game.
B5 — Facade (Conceptual)

Design a GameFacade class for your system. What functions would it expose?
GameFacade akan menyembunyikan kerumitan RunSession, ScoringSystem, dan ShopSystem dari antarmuka pengguna (UI/Terminal utama).
Fungsi yang diekspos (disediakan):

    startGame()

    playSelectedCards(vector<int> cardIndices)

    buyShopItem(int itemID)

    skipShop()

    endGame()

PART C — Behavioral Pattern Analysis
C1 — Strategy

Explain where scoring logic exists.
Logika perhitungan skor dipisahkan sepenuhnya dari RunSession. Logika ini berada di dalam class StandardScoringStrategy::calculateBaseScore(const std::vector<Card>& playedCards) di dalam file src/ScoringSystem.cpp. RunSession hanya melakukan delegasi (meminta hasil hitungan) ke ScoringSystem.

How would you support multiple scoring rules?
Saya bisa mendukung aturan baru dengan membuat class baru (contoh: HardcoreScoringStrategy) yang mengimplementasikan interface IScoringStrategy. Kemudian, saya cukup memanggil scoringSystem->setStrategy(new HardcoreScoringStrategy()) di runtime tanpa harus merombak kode game loop.
C2 — Observer (Conceptual)

Identify events in your system. Explain how Observer could improve design.

    Events: OnCardPlayed, OnScoreCalculated, OnModifierBought.

    Improvement: Observer pattern memungkinkan sistem UI (teks/terminal) atau sistem Achievement (Pencapaian) untuk "mendengarkan" event-event ini secara mandiri. Ini mencegah RunSession memanggil std::cout secara hardcode, membuat pemisahan antara logika game (Data) dan tampilan visual (View) menjadi lebih bersih.

C3 — Command (Conceptual)

Identify actions that could be represented as Command objects.
Tindakan seperti "Membeli Modifier", "Memainkan Kartu (Play Hand)", dan "Melewati Shop" dapat dibungkus sebagai Command objects. Ini sangat berguna jika game ingin menambahkan fitur Undo (membatalkan aksi beli/main) atau menyimpan history replay dari seluruh turn pemain.
C4 — State (Conceptual)

Explain how State pattern could organize run phases.
Fase-fase seperti DrawPhase, PlayPhase, ScoringPhase, dan ShopPhase dapat direpresentasikan sebagai class State tersendiri. RunSession akan menyimpan pointer ke IGameState saat ini. Ini akan mencegah transisi ilegal, misalnya: pemain tidak bisa memanggil aksi "Beli Modifier" jika status game saat ini sedang berada di dalam PlayPhase.