#include <imgui.h>

#include <Ziben/Application.hpp>
#include <Ziben/Scene/Layer.hpp>
#include <Ziben/Renderer/RenderCommand.hpp>

#include <GeneralAlgebra/LongArithmetic.hpp>
#include <GeneralAlgebra/LongNumber.hpp>
#include <GeneralAlgebra/EllipticCurve.hpp>
#include <GeneralAlgebra/IntegerField.hpp>
#include <GeneralAlgebra/Literals.hpp>

class Application;

class CalculatorLayer : public Ziben::Layer {
public:
    CalculatorLayer()
        : Ziben::Layer("CalculatorLayer")
        , m_Operation(Operation::None)
        , m_IsPrimeNumberInputActive(true) {}

public:
    void OnRender() override {
        Ziben::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Ziben::RenderCommand::Clear();
    }

    void OnImGuiRender() override {
        static bool               dockspaceOpen   = true;
        static bool               fullscreen      = true;
        static bool               padding         = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags windowFlags              = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        if (fullscreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

            windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        } else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            windowFlags |= ImGuiWindowFlags_NoBackground;

        if (!padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace", &dockspaceOpen, windowFlags);
        {
            if (!padding)
                ImGui::PopStyleVar();

            if (fullscreen)
                ImGui::PopStyleVar(2);

            // DockSpace
            ImGuiIO&    io    = ImGui::GetIO();
            ImGuiStyle& style = ImGui::GetStyle();

            float windowMinSizeX = style.WindowMinSize.x;
            style.WindowMinSize.x = 370.0f;

            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                ImGuiID dockspace_id = ImGui::GetID("DockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }

            style.WindowMinSize.x = windowMinSizeX;

            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Exit"))
                        std::cout << "close" << std::endl;

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6.0f, 6.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(6.0f, 6.0f));
            ImGui::Begin("Field");
            {
                static char buffer[1000];

                std::strcpy(buffer, m_PrimeNumber.ToString().c_str());

                {
                    float inputWidth  = ImGui::GetContentRegionAvailWidth() * 0.65f - 6.0f;
                    float buttonWidth = ImGui::GetContentRegionAvailWidth() * 0.35f;

                    ImGui::PushItemWidth(inputWidth);

                    if (ImGui::InputText("##PrimeNumber", buffer, sizeof(buffer))) {
                        m_IsPrimeNumberInputActive = true;
                        m_PrimeNumber.SetString(buffer);
                    }

                    ImGui::PopItemWidth();

                    if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                        m_IsPrimeNumberInputActive = true;

                    ImGui::SameLine();

                    if (ImGui::Button("Set PrimeNumber", { buttonWidth, 0.0f }))
                        m_Field.SetPrimeNumber(m_PrimeNumber);
                }

                ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth());

                std::strcpy(buffer, m_Number1.ToString().c_str());

                {
                    if (ImGui::InputText("##Input", buffer, sizeof(buffer))) {
                        m_IsPrimeNumberInputActive = false;
                        m_Number1.SetString(buffer);
                    }

                    if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
                        m_IsPrimeNumberInputActive = false;
                }

//                ImGui::Text("History: %s", m_History.c_str());

                ImGui::PopItemWidth();

                ImVec2 buttonSize = {
                    ImGui::GetContentRegionAvail().x / 4.0f - 6.0f * 4.0f / 5.0f,
                    ImGui::GetContentRegionAvail().y / 6.0f - 6.0f * 5.0f / 6.0f
                };

                {
                    if (ImGui::Button("Clear", {  ImGui::GetContentRegionAvail().x / 4.0f * 3.0f - 2.0f, buttonSize.y })) {
                        m_Operation = Operation::None;
                        m_Number1   = 0;
                        m_Number2   = 0;
                    }

                    ImGui::SameLine();

                    if (ImGui::Button("<", buttonSize))
                        Push('<');
                }

                {
                    if (ImGui::Button("Inv", buttonSize)) {
                        m_Operation = Operation::Inv;
                        m_Number1   = Calculate();
                    }

                    ImGui::SameLine();

                    if (ImGui::Button("Pow", buttonSize)) {
                        m_Operation = Operation::Pow;
                        m_Number2   = std::move(m_Number1);
                    }

                    ImGui::SameLine();

                    if (ImGui::Button("Sqrt", buttonSize)) {
                        m_Operation = Operation::Sqrt;
                        m_Number1   = Calculate();
                    }

                    ImGui::SameLine();

                    if (ImGui::Button("/", buttonSize)) {
                        m_Operation = Operation::Div;
                        m_Number2   = std::move(m_Number1);
                    }
                }

                {
                    if (ImGui::Button("7", buttonSize))
                        Push('7');

                    ImGui::SameLine();

                    if (ImGui::Button("8", buttonSize))
                        Push('8');

                    ImGui::SameLine();

                    if (ImGui::Button("9", buttonSize))
                        Push('9');

                    ImGui::SameLine();

                    if (ImGui::Button("*", buttonSize)) {
                        m_Operation = Operation::Mul;
                        m_Number2   = std::move(m_Number1);
                    }
                }

                {
                    if (ImGui::Button("4", buttonSize))
                        Push('4');

                    ImGui::SameLine();

                    if (ImGui::Button("5", buttonSize))
                        Push('5');

                    ImGui::SameLine();

                    if (ImGui::Button("6", buttonSize))
                        Push('6');

                    ImGui::SameLine();

                    if (ImGui::Button("+", buttonSize)) {
                        m_Operation = Operation::Add;
                        m_Number2   = std::move(m_Number1);
                    }
                }

                {
                    if (ImGui::Button("1", buttonSize))
                        Push('1');

                    ImGui::SameLine();

                    if (ImGui::Button("2", buttonSize))
                        Push('2');

                    ImGui::SameLine();

                    if (ImGui::Button("3", buttonSize))
                        Push('3');

                    ImGui::SameLine();

                    if (ImGui::Button("-", buttonSize)) {
                        m_Operation = Operation::Sub;
                        m_Number2   = std::move(m_Number1);
                    }
                }

                {
                    if (ImGui::Button("0", { ImGui::GetContentRegionAvail().x / 4.0f * 3.0f - 2.0f, buttonSize.y }))
                        m_Number1 = m_Number1.ToString() + "0";

                    ImGui::SameLine();

                    if (ImGui::Button("=", buttonSize)) {
                        auto result = Calculate();

                        m_Number1 = result;
                        m_Number2 = result;
                    }
                }
            }
            ImGui::End();
            ImGui::PopStyleVar(2);

//            ImGui::Begin("Elliptic Curve");
//            {
//
//            }
//            ImGui::End();

//            ImGui::ShowDemoWindow();
        }
        ImGui::End();
    }

private:
    using LongNumber = GeneralAlgebra::LongNumber9;
    using Field      = GeneralAlgebra::IntegerField<LongNumber>;

    using History    = std::vector<std::string>;

private:
    enum class Operation : uint8_t { None = 0, Add, Sub, Mul, Div, Pow, Sqrt, Inv };

private:
    void Push(char symbol) {
        auto& activeNumber = m_IsPrimeNumberInputActive ? m_PrimeNumber : m_Number1;

        if (symbol != '<') {
            activeNumber = activeNumber.ToString() + symbol;
            return;
        }

        auto string = activeNumber.ToString();
        string.pop_back();
        activeNumber = string;
    }

    LongNumber Calculate() {
        LongNumber result;

        switch (m_Operation) {
            case Operation::Add:  result = m_Field.Add(m_Number2, m_Number1); break;
            case Operation::Sub:  result = m_Field.Sub(m_Number2, m_Number1); break;
            case Operation::Mul:  result = m_Field.Mul(m_Number2, m_Number1); break;
            case Operation::Div:  result = m_Field.Div(m_Number2, m_Number1); break;
            case Operation::Pow:  result = m_Field.Pow(m_Number2, m_Number1); break;
            case Operation::Sqrt: result = m_Field.Sqrt(m_Number1).first;     break;
            case Operation::Inv:  result = m_Field.GetInverse(m_Number1);     break;
            default:                                                          break;
        }

        m_Number1 = LongNumber::Null;
        m_Number2 = LongNumber::Null;

        return result;
    }

private:
    LongNumber m_PrimeNumber;
    Field      m_Field;

    LongNumber m_Number1;
    LongNumber m_Number2;
    Operation  m_Operation;

    bool       m_IsPrimeNumberInputActive;

    History    m_History;

}; // class CalculatorLayer

class Application : public Ziben::Application {
public:
    Application()
        : Ziben::Application("LabGA", 400, 600) {

        PushLayer(new CalculatorLayer);
    }
};

Ziben::Application* Ziben::CreateApplication(int argc, char **argv) {
    (void)argc;
    (void)argv;

    return new ::Application;
}

#if 0

int main() {
#if 0
    BaseTable(10, 16);
    KaratsubaTable(10, 14);
    MulTable<9>(5, 17);
    DivTable<3>(5, 13);
#endif

    using namespace GeneralAlgebra::Literals;

//    GeneralAlgebra::LongNumber<2> number(100);
//    GeneralAlgebra::LongNumber<2> pow(100);

//    GeneralAlgebra::IntegerField<GeneralAlgebra::LongNumber<2>> field5(157_ln2);
//    auto res = field5.Pow(number,pow);
//    std::cout<<res;

//    std::cout << number.Pow(pow) << std::endl;

//    std::bitset<8> bs(123);

//    std::cout << bs.to_string() << std::endl;

//    GeneralAlgebra::LongNumber<9> a("1965367186937344331092315976815654895"
//                                    "46150885535661729204775107878748576350456794"
//                                    "250132052419920164252336986766776254871552007"
//                                    "511456852558708258131223895295");
//    GeneralAlgebra::LongNumber<9> n("9652938498042438064030577109725184210"
//                                    "87341028384581503390226504627927666655113708"
//                                    "73080552058053523529615216061121230838122275"
//                                    "72180692166017047090139433108589657111514487"
//                                    "45719806499654469016163567161346874008170746"
//                                    "694186189093232534605065851033323868778630628"
//                                    "326524881117169625057400354660768978977891");
//    GeneralAlgebra::IntegerField<GeneralAlgebra::LongNumber<9>> field(n);
//    GeneralAlgebra::LongNumber<9> q(3);
//    auto p = field.Sqrt(a);
//    int i = 1;
//    while(p.first == GeneralAlgebra::LongNumber<9>::Null){
//        std::cout << "Iteration #N " << i << std::endl;
//        a -= q;
//        std::cout << "After -=q" << std::endl;
//        p = field.Sqrt(a);
//        std::cout << "After Sqrt" << std::endl;
//        q *= q;
//        std::cout << "After *=q" << std::endl;
//    }
//    std::cout << p.first << " " << p.second << "\n";
//    std::cout << "Jacobi(a,n) = " << GeneralAlgebra::LongArithmetic::Jacobi(a,n) << "\n";
//    std::cout << (field.Mul(p.first, p.first) == a) << "\n";

    using namespace GeneralAlgebra;
    using namespace GeneralAlgebra::Literals;

    LongNumber7 a;
    LongNumber8 b;

    a = 123u;
    b = "32492387452384792";

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;

    using EllipticCurve = EllipticCurve<LongNumber3>;

    EllipticCurve ellipticCurve(1_ln3, 0_ln3, 13_ln3);

    EllipticCurve::Point point1 = { 2_ln3, 6_ln3 };
    EllipticCurve::Point point2 = { 3_ln3, 2_ln3 };

    EllipticCurve::Point point3 = { 6_ln3, 1_ln3 };
    EllipticCurve::Point point4 = { 5_ln3, 0_ln3 };

    auto result1 = ellipticCurve.Add(point1, point2);
    auto result2 = ellipticCurve.GetInverse(point3);
    auto result3 = ellipticCurve.GetInverse(point4);

    std::cout << "Add:       " << result1.X << " " << result1.Y << std::endl;
    std::cout << "Expected:  " << 11 << " " << 4 << std::endl;

    std::cout << "Inverse1:  " << result2.X << " " << result2.Y << std::endl;
    std::cout << "Expected:  " << 6 << " " << 12 << std::endl;

    std::cout << "Inverse2:  " << result3.X << " " << result3.Y << std::endl;
    std::cout << "Expected:  " << 5 << " " << 0 << std::endl;

    return 0;
}

#endif