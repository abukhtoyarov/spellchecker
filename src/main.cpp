#include <iostream>
#include <string>
#include <clocale>
#include "spellchecker.hpp"
#include <chrono>

template <class Fn, class... Args>
auto timer(Fn fn, Args... args) {
    using namespace std::chrono;
    auto start = high_resolution_clock::now();
    std::forward<Fn>(fn)(std::forward<Args>(args)...);
    auto end = high_resolution_clock::now();
    duration<double, std::milli> elapsed_seconds = end - start;
    return elapsed_seconds.count();
}

static const wchar_t *dic = L"В группе, проектирующей посадочный лунный модуль, шла долгая дискуссия:\
    какую поверхность имеет Луна. От этого зависело, какую конструкцию выбрать для посадочного модуля.\
    Выдвигались равнодостоверные аргументы в пользу многометровой пыли, песчаной пустыни, твёрдой\
    поверхности… Отсутствие решения стало тормозить дальнейшую работу. Присутствующий на очередном\
    безрезультатном заседании Сергей Павлович принял волевое решение и написал: ... следует рассчитывать\
    на достаточно твёрдый грунт типа пемзы. Луна привлекала внимание людей с древних времён. Во II в. до н. э.\
    Гиппарх исследовал движение Луны по звёздному небу, определив наклон лунной орбиты относительно эклиптики,\
    размеры Луны и расстояние от Земли[1], а также выявил ряд особенностей движения. Полученную Гиппархом теорию\
    развил впоследствии астроном из Александрии Клавдий Птолемей во II веке н. э., написав об этом книгу «Альмагест».\
    Данная теория множество раз уточнялась, и в 1687 году, после открытия Ньютоном закона всемирного тяготения,\
    из чисто кинематической, описывающей геометрические свойства движения, теория стала динамической, учитывающей\
    движение тел под действием приложенных к ним сил. Изобретение телескопов позволило различать более мелкие\
    детали рельефа Луны. Одну из первых лунных карт составил Джованни Риччиоли в 1651 году, он же дал названия\
    крупным тёмным областям, наименовав их «морями», чем мы и пользуемся до сих пор. Данные топонимы отражали давнее\
    представление, будто погода на Луне схожа с земной, и тёмные участки якобы были заполнены лунной водой, а светлые\
    участки считались сушей. Однако в 1753 году хорватский астроном Руджер Бошкович доказал, что Луна не имеет\
    атмосферы. Дело в том, что при покрытии звёзд Луной те исчезают мгновенно. Но если бы у Луны была атмосфера,\
    то звезды бы погасали постепенно. Это свидетельствовало о том, что у спутника нет атмосферы. А в таком случае\
    жидкой воды на поверхности Луны быть не может, так как она мгновенно бы испарилась. С лёгкой руки того же Джованни\
    Риччиоли кратерам стали давать имена известных учёных: от Платона, Аристотеля и Архимеда до Вернадского, Циолковского и Павлова.\
    После окончания советской космической программы «Луна» и американской «Аполлон» исследования Луны с помощью космических аппаратов\
    были практически прекращены. Но в начале XXI века Китай опубликовал свою программу освоения Луны, включающую после доставки\
    лунохода и отправки грунта на Землю затем экспедиции на Луну и постройку обитаемых лунных баз. Считается, что это заставило\
    остальные космические державы снова развернуть лунные программы как новую «лунную гонку за второе место». О планах будущих\
    лунных экспедиций заявили Россия, Европа, Индия, Япония, а президент Дж. Буш 14 января 2004 года объявил, что США начинают\
    масштабную детальную программу «Созвездие» с созданием новых ракет-носителей и пилотируемых космических кораблей,\
    способных к 2020 году доставить на Луну людей и большие обитаемые луноходы, с целью заложить первые лунные базы.\
    Программа «Созвездие» в лунной части была отменена через 5 лет президентом Бараком Обамой. Европейское космическое агентство 28\
    сентября 2003 года запустило свою первую автоматическую межпланетную станцию (АМС) «Смарт-1». 14 сентября 2007 года Япония\
    запустила вторую АМС для исследования Луны «Кагуя». А 24 октября 2007 года в лунную гонку вступила и КНР — был запущен первый\
    китайский спутник Луны «Чанъэ-1». С помощью этой и следующей станций учёные создают объёмную карту лунной поверхности,\
    что в будущем может поспособствовать амбициозному проекту колонизации Луны[8]. 22 октября 2008 года была запущена первая\
    индийская АМС «Чандраян-1». В 2010 году Китай запустил вторую АМС «Чанъэ-2». Место посадки экспедиции Аполлон-17. Видны:\
    спускаемый модуль, исследовательское оборудование ALSEP, следы колёс автомобиля и пешие следы космонавтов.\
    Снимок КА LRO, 4 сентября 2011 года. 18 июня 2009 года, НАСА были запущены лунные орбитальные зонды — Lunar\
    Reconnaissance Orbiter (LRO) и Lunar Crater Observation and Sensing Satellite (LCROSS). Спутники предназначены\
    для сбора информации о лунной поверхности, поиска воды и подходящих мест для будущих лунных экспедиций[9].\
    К сорокалетию полёта Аполлона-11 автоматическая межпланетная станция LRO выполнила специальное задание — \
    провела съёмку районов посадок лунных модулей земных экспедиций. В период с 11 по 15 июля LRO сделала и\
    передала на Землю первые в истории детальные орбитальные снимки самих лунных модулей, посадочных площадок,\
    элементов оборудования, оставленных экспедициями на поверхности, и даже следов тележки, ровера и самих землян.\
    За это время были отсняты 5 из 6 мест посадок: экспедиции Аполлон-11, 14, 15, 16, 17[11]. Позднее КА LRO выполнил\
    ещё более подробные снимки поверхности, где ясно видно не только посадочные модули и аппаратуру со следами лунного\
    автомобиля, но и пешие следы самих космонавтов[12]. 9 октября 2009 космический аппарат LCROSS и разгонный блок «Центавр»\
    совершили запланированное падение на поверхность Луны в кратер Кабеус, расположенный примерно в 100 км от южного полюса Луны,\
    а потому постоянно находящийся в глубокой тени. 13 ноября НАСА сообщило о том, что с помощью этого эксперимента на Луне\
    обнаружена вода. К изучению Луны приступают частные компании. Был объявлен всемирный конкурс Google Lunar X PRIZE по\
    созданию небольшого лунохода, в котором участвуют несколько команд из разных стран, в том числе российская Селеноход.\
    В 2014 году появилась первая частная лунно-облётная АМС (Manfred Memorial Moon Mission). Есть планы по организации космического\
    туризма с полётами вокруг Луны на российских кораблях — сначала на модернизированных «Союзах», а затем на разрабатываемых\
    перспективных универсальных ПТК НП («Русь»). США собираются продолжать исследования Луны автоматическими станциями GRAIL\
    (запущенной в 2011 году), LADEE (запущенной в 2013 году) и другими. Китай запустил свою первую лунно-посадочную АМС «Чанъэ-3»\
    с первым луноходом в декабре 2013 года и первую лунно-облётную АМС с возвращаемым аппаратом в 2014 году, затем в декабре\
    2018 прошёл запуск \"Чанъэ-4\" с луноходом \"Юйту-2\", а далее планирует АМС, возвращающую лунный грунт, к 2019 году в преддверии\
    пилотируемых полётов около 2025 года и строительства лунной базы к 2050 году[источник не указан 2356 дней] Япония объявила о будущих\
    исследованиях Луны роботами. Индия планирует миссию в 2017 году своего орбитального аппарата «Чандраян-2» и\
    небольшого лунохода, доставляемого российской АМС «Луна-Ресурс», и дальнейшие исследования Луны вплоть до пилотируемых\
    экспедиций. Россия сначала запускает многоэтапную программу исследования Луны автоматическими станциями «Луна-Глоб» в 2015 году,\
    «Луна-Ресурс-2» и «Луна-Ресурс-3» с луноходами в 2020 и 2022 гг, «Луна-Ресурс-4» по возврату собранного луноходами грунта в 2023 году,\
    а затем планирует пилотируемые экспедиции в 2030-х гг. Не исключено, что на Луне может находиться не только серебро, ртуть и спирты, но\
    и прочие химические элементы и соединения. Водяной лёд, молекулярный водород, найденные благодаря миссии LCROSS и LRO в лунном\
    кратере Кабеус указывают на то, что на Луне действительно есть ресурсы, которые могут быть использованы в будущих миссиях.\
    Анализ топографических данных, присланных аппаратом LRO, и гравитационные измерения «Кагуя» показали, что толщина коры на\
    обратной стороне Луны не постоянна и меняется с широтой места. Самые толстые участки коры соответствуют наибольшим возвышенностям,\
    что характерно и для Земли, а самые тонкие обнаружены в приполярных широтах";

int main(int , char **) {
    using namespace spellchecker;
    setlocale(LC_ALL,"ru_RU.UTF-8");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));
    std::wcin.imbue(std::locale("ru_RU.UTF-8"));
    
    Spellchecker<wchar_t> sc;

    std::wcout << L"Load time: " << timer([&](){ sc.load(dic); }) << L"ms" << std::endl;
    sc.accuracy(2);
    
    static std::wstring str = L"Лун привлекапа внимание людей с древних врем. Пирамида.";
    
    std::list<Result<wchar_t>> results;
    std::wcout << L"Check time: " << timer([&](){ results = sc.check(str); })  << L"ms" << std::endl;
   
    for(const auto &r: results) {
        switch(r.state_) {
        
        case State::correct: {
            std::wcout << L"Correct: " << r.word_ << std::endl;
        } break;
        
        case State::options: {
            std::wcout << L"Wrong but there are options: " << r.word_ << std::endl;
            for(const auto &o: r.data_) {
                std::wcout 
                    << L"    >> " 
                    << L"d:" << o.first 
                    << L" " << o.second
                    << std::endl;
            }
        } break;

        case State::wrong: {
            std::wcout << L"Wrong: " << r.word_ << std::endl;
        } break;

        default:
            throw std::runtime_error("unexpected");
        };
    }
    return 0;
}

// Load time: 36,64ms
// Check time: 8,91574ms
// Wrong but there are options: лун
//     >> d:1 луну
//     >> d:1 луне
//     >> d:1 луны
//     >> d:1 луна
//     >> d:2 лет
// Wrong but there are options: привлекапа
//     >> d:1 привлекала
// Correct: внимание
// Correct: людей
// Correct: с
// Correct: древних
// Wrong but there are options: врем
//     >> d:1 время
//     >> d:2 чем
//     >> d:2 времён
// Wrong: пирамида
