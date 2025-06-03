### Kniflash

#### 一. 文件树

```cpp
.
├─include #头文件存储目录
├─resource #资源文件存储目录 
│  ├─font #字体存储目录
│  ├─image #图片存储目录
│  │  ├─background #背景
│  │  ├─character #人物动画
│  │  └─icon #特效，图标
│  └─sound #音效存储目录
├─SFML #SFML库目录
│  ├─bin
│  ├─include
│  │  └─SFML
│  │      ├─Audio
│  │      ├─Graphics
│  │      ├─Network
│  │      ├─System
│  │      └─Window
│  └─lib
│      └─cmake
│          └─SFML
├─src #源代码存储目录
```

#### 二. 类，方法，辅助函数描述

- **Animation：动画类**

    ```cpp
    class Animation {
    private:
        float currentTime, duration; //动画播放时间
        std :: vector<Frame> list; //帧序列
        size_t it; //当前播放帧
        bool loop, paused; //动画是否循环，暂停
    public:
        Animation(const std :: vector<Frame> &list = (std :: vector<Frame>){}, const float &duration = 0, bool loop = true);
        virtual ~Animation();
        void setLoop(bool loop = true);
        void pause(); //动画暂停
        void run(); //动画播放
        bool end() const; //动画是否播放完毕
        void play(sf :: Sprite *sprite, const float &deltaTime); //将动画当前帧加载至 Sprite 对象中
        void reset(); //动画重置
    };
    
    ```

- **Border：地图边界**

    ```cpp
    class Border : public Entity {
    private:
        sf :: Vector2f base; //中心
        float radius; //半径
        int layer, order; //对象层，优先级
        const float velocity = 100.f; //半径缩小速度
    public:
        Border(sf :: Vector2f base, float radius, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
        virtual ~Border();
        void set(sf :: Vector2f base, float radius); //设置中心，半径
        sf :: Vector2f getBase() const; //获取中心
        sf :: Vector2f randomPoint() const; //边界内随机一点
        float getRadius() const; //获取半径
        bool check(sf :: Vector2f position) const; //检查是否在边界内
        sf :: Vector2f constrains(sf :: Vector2f position) const; //调整坐标至边界内
        virtual void update(const float &deltaTime); //更新函数
    };
    ```

- **Bush：树丛**

    ```cpp
    class Bush : public Entity {
    private:
        const float minimalDistance = 1000.f; //树丛最小间距
        const Border* border; //边界指针
        int number, layer, order; //树丛数量，对象层，优先级
        bool check(sf :: Vector2f position) const; //检查树丛位置是否合法
    public:
        Bush(const Border* border, int number, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
        virtual ~Bush();
        void set(int number); //设置树丛数目
    };
    ```

- **Button：按钮**

    ```cpp
    class Button : public Entity {
    private:
        uint64_t receiver; //信号接收者
        std :: string signal; //信号
        bool pressed = false, activated = false; //按钮是否按下，激活
        sf :: Text* character = nullptr; //按钮标签
    public:
        Button(uint64_t receiver, const std :: string &signal, const std :: wstring & text, sf :: Font* font, int size, const sf :: Vector2f &position, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
        virtual ~Button();
        sf :: Text* get(); //获取按钮标签
        virtual void update(const float &deltaTime); //更新函数
    };
    ```

- **DynamicEntity：拥有动画的对象**

    ```cpp
    class DynamicEntity : public Entity {
    private:
        sf :: Sprite sprite; //sprite 对象
        int layer, order; bool fixed = false; //对象层，优先级，是否锁定切换
        std :: map<std :: string, Animation> animations; //所有动画
        std :: string currentAnimation = ""; //当前动画名称
    public:
        DynamicEntity(int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
        virtual ~DynamicEntity();
        void add(const std :: string &key, const Animation &value); //增加动画
        void play(std :: string key, bool priority = false); //播放对应动画
        sf :: Sprite* get();
        void reset(); //当前动画重置
        const Animation* getAnimation(const std :: string& animation) const; //获取当前动画
        virtual void update(const float& deltaTime); //更新函数
    };
    ```

- **EllipseShape：椭圆**

    ```cpp
    class EllipseShape : public sf :: Shape {
    public:
        explicit EllipseShape(sf::Vector2f radius = {0, 0}) : m_radius(radius) {
            update();
        }
        void setRadius(sf::Vector2f radius) {//设置椭圆半径
            m_radius = radius;
            update();
        }
        sf::Vector2f getRadius() const {//获取椭圆半径
            return m_radius;
        }
        std::size_t getPointCount() const override {//获取椭圆顶点个数
            return 30;
        }
        sf :: Vector2f getPoint(std :: size_t index) const override {//获取椭圆对应顶点
            static constexpr float pi = 3.141592654f;
            float angle = index * 2 * pi / getPointCount() - pi / 2;
            float x     = std :: cos(angle) * m_radius.x;
            float y     = std :: sin(angle) * m_radius.y;
            return m_radius + sf::Vector2f(x, y);
        }
    private:
        sf :: Vector2f m_radius;//椭圆半径
    };
    ```

- **EndScene：结束场景**

    ```cpp
    class EndScene : public Entity {
    public:
        EndScene(sf :: RenderWindow* window, int skin, float clock, std :: pair<int, int> rank, int kills);
        virtual ~EndScene();
        virtual void update(const float& deltaTime);//更新动画
    };
    ```

- **EnemyController：npc 控制对象**

    ```cpp
    class EnemyController : public Entity {
    private:
        uint64_t cx[2], cy[2];//x轴与y轴运动参数
        float interval = 0.f;//运动随机决策时隔
        float delta = 0.f;//运动时间
        float attackProbability = 0.f;//攻击可能性
        const int maxn = 10;//随机参数
        bool targeted = false;//是否锁定对象
        void move(sf :: Vector2f pos, bool reverse = false);//向指定方向移动
    public:
        EnemyController(const std :: vector<std :: string> &tag = {});
        virtual ~EnemyController();
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **Entity：所有对象的基类**

    ```cpp
    class Entity {
    private:
        Entity* ancestor;//父亲节点
        uint64_t id;//节点id
        std :: map<std :: string, bool> tags;//节点tag
        std :: map<std :: string, std :: vector<Entity*> > sub;//所有子节点tag与指针映射
        std :: map<uint64_t, Entity*> ids;//所有子节点id与指针映射
        sf :: RenderWindow* window;//窗口
    protected:
        std :: vector<Entity*> components;//子节点
    public:
        sf :: Transform transform;//相对父节点变换
        Entity(const std :: vector<std :: string> &tag = {}, sf :: RenderWindow* window = nullptr);
        virtual ~Entity();
        Entity* super();//获取父节点
        Entity* root();//获取根节点
        uint64_t uuid() const;//获取当前节点id
        sf :: RenderWindow* getWindow() const;//获取窗口指针
        bool contains(const std :: string& tag) const;//是否包含某一tag
        sf :: Transform getTransform() const;//获取当前节点绝对变换
        void addChild(Entity* child);//增加子节点
        std :: vector<Entity*> find(const std :: string &tag);//查找包含某一tag子节点指针
        Entity* find(uint64_t uuid);//查找对应id子节点指针
        virtual void update(const float& deltaTime);//更新函数
    };
    
    ```

- **FlyKnife：飞刀对象**

    ```cpp
    class FlyKnife : public Entity {
    private:
        uint64_t owner;//飞刀拥有对象
        sf :: Vector2f pos, v;//位置，方向
        const float velocity = 4500.f, maxd = 1500.f;//飞刀速度，射程
        float delta = 0.f;//飞行时间
    
    public:
        FlyKnife(uint64_t owner, const sf :: Vector2f &pos, const sf :: Vector2f &v, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
        virtual ~FlyKnife();
        bool isActive() const;//是否在射程内
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **Frame：动画帧类**

    ```cpp
    class Frame {
    private:
        sf :: Texture* texture//所对应texture指针
        sf :: IntRect rect;//边界位置
        sf :: Vector2f origin;//中心点
    public:
        Frame(sf :: Texture* texture = nullptr, const sf :: IntRect &rect = sf :: IntRect(), const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));
        ~Frame();
        void load(sf :: Sprite* sprite) const;//将当前帧载入sprite对象
    };
    std :: vector<Frame> combineFrame(sf :: Texture* texture, const sf :: Vector2i &start, const sf :: Vector2i &end, const sf :: Vector2i &size, const sf :: Vector2f &origin = sf :: Vector2f(0.f, 0.f));//辅助函数，将对应texture，起始位置，终止位置包装为帧序列
    
    ```

- **Game：游戏类**

    ```cpp
    class Game {
    private:
        float height, width;//窗口高度，宽度
        sf :: RenderWindow window;//窗口对象
        sf :: Event event;//当前事件
        sf :: Clock clock;//时钟
        float deltaTime;//帧间时长
        Entity* scene = nullptr;//当前场景
        
    public:
        Game();
        virtual ~Game();
        void update();//更新函数
        void render();//渲染函数
        void run();//运行函数
    };
    ```

- **GameScene：游戏场景类**

    ```cpp
    class GameScene : public Entity {
    private:
        float clock = 0.f;//游戏运行时长
        const int enemyCount = 49;//敌人数量
    public:
        std :: tuple<int, float, std :: pair<int, int>, int> data();//获取游戏数据，传递给结束场景
        GameScene(sf :: RenderWindow* window);
        virtual ~GameScene();
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **HealthBar：血槽对象**

    ```cpp
    class HealthBar : public Entity {
    private:
        uint64_t owner;//血槽拥有者
        int layer, order;//对象层，优先级
        const int maxHealth = 5;//最大血量
        int health = maxHealth;//当前血量
    public:
        HealthBar(uint64_t owner, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
        virtual ~HealthBar();
        void add();//增加血量
        void inc();//减少血量
        void recover();//恢复满血
        int getNumber() const;//获取当前血量
        virtual void update(const float &deltaTime);//更新函数
    };
    
    ```
    
- **Hitbox：碰撞框**

    ```cpp
    class Hitbox : public RectEntity {
    private:
        std :: string target;//碰撞对象标签
        std :: string signal;//碰撞后发出信号
        int content;//信号内容
        bool active = true;//是否被碰撞
    public:
        Hitbox(sf :: FloatRect rect, const std :: string &target, const std :: string &signal, int content = 0, const std :: vector<std :: string> &tag = {});
        virtual ~Hitbox();
        void reset();//重置当前碰撞框
        bool isActive() const;//判断是否未被碰撞
        virtual void update(const float &deltaTime);//更新函数
    };
    
    ```

- **KillNumber：击杀数目对象**

    ```cpp
    class KillNumber : public Entity {
    private:
        int layer, order;//对象层，优先级
        int kill = 0;//击杀数量
    public:
        KillNumber(int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
        virtual ~KillNumber();
        void set(int number);//设置击杀数量
    };
    ```

- **KnifeCircle：飞刀环绕圈**

    ```cpp
    class KnifeCircle : public Entity {
    private:
        const int maxNumber = 30;//飞刀最大数目
        float velocity = 200.f, radius = 45.f, delta = 12.f;//旋转速度，半径，增加半径
    public:
        KnifeCircle(int number = 4, const std :: vector<std :: string> &tag = {});
        virtual ~KnifeCircle();
        void setNumber(int number);//设置飞刀数量
        int getNumber() const;//获取当前飞刀数量
        void add();//增加飞刀
        void inc();//减少飞刀
        float getRadius() const;//获取飞刀圈半径
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **KnifeManager：管理所有飞行飞刀**

    ```cpp
    class KnifeManager : public Entity {
    public:
        KnifeManager(const std :: vector<std :: string> &tag = {});
        virtual ~KnifeManager();
        virtual void update(const float& deltaTime);//更新函数
    };
    
    ```

- **LineDrawer：追踪线条绘制类**

    ```cpp
    class LineDrawer : public Entity {
    private:
        const float radius = 5.f;//虚线粗细
        std :: vector<Entity*> rub;//存储回收对象
    public:
        LineDrawer(const std :: vector<std :: string> &tag = {});
        virtual ~LineDrawer();
        void draw(const sf :: Vector2f &start, const sf :: Vector2f &end, float delta, int layer = 0, int order = 0); //绘制线条
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **Minimap：小地图**

    ```cpp
    class Minimap : public Entity {
    private:
        const Border* border;//边界指针
        int size; float radius, circleSize;//小地图大小，半径，边框大小
        const float d = 8.f;//人物方框大小
        bool active = true;//是否显示
    public:
        Minimap(const Border* border, int size, const std :: vector<std :: string> &tag = {});
        virtual ~Minimap();
        void hide();//隐藏小地图
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **Objects：游戏中可拾取对象**

    ```cpp
    class Objects : public Entity {
    private:
        const float minimalDistance = 100.f;//对象间最小间距
        const Border* border;//边框指针
        int layer, order;//对象层，优先级
        const int knifeNumber = 45;//飞刀数量
        const int speedNumber = 8;//加速数量
        const int healthNumber = 4;//回血数量
        bool check(sf :: Vector2f position) const;//检查对象位置是否合法
        void set(Entity* obj) const;//放置对象
    public:
        Objects(const Border* border, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {});
        virtual ~Objects();
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **Player：玩家对象**

    ```cpp
    class Player : public Entity {
    private:
        const Border* border;//边框指针
        sf :: Vector2f velocity;//移动速度
        float maxVelocity = 800.f, acceleration = 3000.f, deceleration = 1500.f;//移动速度，加速度
        bool direction = true, active = true, dead = false;//方向，是否活跃，是否死亡
        uint64_t attacker = 0; int skin = 0;//最近受攻击者，角色皮肤编号
        bool interactive;//是否会受到伤害
        void attack(const sf :: Vector2f &u);//向指定方向攻击
        void combat();//近身攻击
        void hurt();//受伤
        void move(const float &x, const float &y, const float &deltaTime);//移动函数
        uint64_t nearest();//最近玩家编号
    public:
        Player(const Border* border = nullptr, const std :: vector<std :: string> &tag = {}, bool interactive = true);
        virtual ~Player();
        void hide();//隐藏当前玩家
        bool isActive() const;//是否活跃
        bool isDead() const;//是否死亡
        int getSkin() const;//获取皮肤编号
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **PlayerController：玩家控制对象**

    ```cpp
    class PlayerController : public Entity {
    public:
        PlayerController(const std :: vector<std :: string> &tag = {});
        virtual ~PlayerController();
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **RectEntity：边框**

    ```cpp
    class RectEntity : public Entity {
    private:
        sf :: FloatRect rect;//边框
        sf :: RectangleShape outline;//绘制对象
    public:
        RectEntity(sf :: FloatRect rect, const std :: vector<std :: string> &tag = {});
        virtual ~RectEntity();
        sf :: FloatRect getLocalRect() const;//获取相对边框
        sf :: FloatRect getGlobalRect() const;//获取绝对边框
        void setRect(sf :: FloatRect rect);//设置边框
        void render();//绘制边框
        virtual void update(const float &deltaTime);//更新函数
    };
    ```

- **RenderPool：对象绘制池**

    ```cpp
    class RenderPool {
    private:
        std :: vector<std :: pair<std :: pair<int, int>, std :: pair<sf :: Drawable*, sf :: Transform> > > pool;//等待渲染对象
    public:
        void add(sf :: Drawable* obj, sf :: Transform transform = sf :: Transform(), int layer = 0, int order = 0);//增加对象
        void render(sf :: RenderTarget* target);//渲染函数
    };
    ```

- **Resource：资源加载池**

    ```cpp
    class Resource {
    private:
        std :: map <std :: string, sf :: Texture*> img;//图像资源
        std :: map <std :: string, sf :: Font*> font;//字体资源
        std :: map <std :: string, sf :: SoundBuffer*> soundBuffer;//音效资源
        std :: map <std :: string, sf :: Sound*> sound;//声音资源
        
        void loadImg(const std :: filesystem :: path &directory);//加载图像
        void loadFont(const std :: filesystem :: path &directory);//加载字体
        void loadSound(const std :: filesystem :: path &directory);//加载声音
    public:
        Resource();
        virtual ~Resource();
        void loadFrom(const std :: filesystem :: path &directory);//加载函数
        sf :: Texture* getImg(const std :: string &file) const;//获取图像
        sf :: Font* getFont(const std :: string &file) const;//获取字体
        sf :: Sound* getSound(const std :: string &file) const;//获取声音
    };
    ```
    
- **Rotater：旋转实例**

    ```cpp
    class Rotater : public Entity {
    private:
        float velocity;//旋转速度
    public:
        Rotater(const float &velocity, const std :: vector<std :: string> &tag = {});
        virtual ~Rotater();
        virtual void update(const float &deltaTime);//更新函数
    };
    ```

- **ShapeCopier：Shape 复制类**

    ```cpp
    class ShapeCopier : public Entity {
    private:
        sf :: Shape* shape;//复制对象
        int maxNumber;//最大复制数量
        float interval, velocity, current = 0.f;//复制时间间隔，透明度减少速度，当前时间
        int layer, order;//对象层，优先级
        bool active = true;//是否更新
    public:
        ShapeCopier(sf :: Shape* sprite, int maxNumber, float interval, float velocity, int layer = 0, int order = 0, const std :: vector<std :: string> &tags = {});
        virtual ~ShapeCopier();
        void set(bool active);//设置状态
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **SignalPool：信号池**

    ```cpp
    class SignalPool {
    private:
        std :: map<uint64_t, std :: map<std :: string, uint64_t> > pool;//所有信号
    public:
        void clear();//清空信号池
        void add(uint64_t receiver, const std :: string &signal, uint64_t content = 0);//增加信号
        bool contains(uint64_t owner, const std :: string &signal) const;//是否包含信号
        void del(uint64_t owner, const std :: string &signal);//删除信号
        uint64_t query(uint64_t owner, const std :: string &signal) const;//查询信号内容
    };
    ```

- **SoundPlayer：音效播放类**

    ```cpp
    class SoundPlayer : public Entity {
    private:
        const float k = 0.0002f;//音效缩减参数
        std :: string listener;//接受声音对象tag
        std :: vector<sf :: Sound*> sounds;//声音实例
    public:
        SoundPlayer(const std :: string &listener, const std :: vector<std :: string> &tag = {});
        virtual ~SoundPlayer();
        void play(const std :: string &name);//播放指定声音
        virtual void update(const float &deltaTIme);//更新函数
    };
    ```

- **SpriteCopier：Sprite 复制类**

    ```cpp
    class SpriteCopier : public Entity {
    private:
        sf :: Sprite* sprite;//复制对象
        int maxNumber;//最大复制数目
        float interval, velocity, current = 0.f;//复制间隔，透明度减少速度，当前时间
        int layer, order;//对象层，优先级
        bool active = true;//是否更新
    public:
        SpriteCopier(sf :: Sprite* sprite, int maxNumber, float interval, float velocity, int layer = 0, int order = 0, const std :: vector<std :: string> &tags = {});
        virtual ~SpriteCopier();
        void set(bool active);//设置状态
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **StartScene：开始界面**

    ```cpp
    class StartScene : public Entity {
    private:
        const int enemyCount = 6;//显示敌人数量
    public:
        StartScene(sf :: RenderWindow* window);
        virtual ~StartScene();
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **StaticEntity：静态对象**

    ```cpp
    class StaticEntity : public Entity {
    private:
        sf :: Drawable* obj;//需要渲染对象
        int layer, order;//对象层，优先级
        bool active = true, combineTransform;//是否显示，是否采用相对变换
    public:
        StaticEntity(sf :: Drawable *obj = nullptr, int layer = 0, int order = 0, const std :: vector<std :: string> &tag = {}, bool combineTransform = true);
        virtual ~StaticEntity();
        void set(sf :: Drawable *obj);//设置对象
        void setStatus(bool status);//设置是否显示
        sf :: Drawable* get();//获取对象
        virtual void update(const float& deltaTime);//更新函数
    };
    ```

- **Statistics：数据统计类**

    ```cpp
    class Statistics : public Entity {
    private:
        std :: map<uint64_t, int> kills;//所有玩家与击杀数映射
    public:
        Statistics(const std :: vector<std :: string> &tag = {});
        virtual ~Statistics();
        void add(uint64_t uuid);//增加玩家击杀
        int query(uint64_t uuid);//查询玩家击杀
    };
    ```

- **Timer：计时器**

    ```cpp
    class Timer : public Entity {
    private:
        float duration, currentTime;//倒计时长，当前时间
        uint64_t receiver;//信号接收者
        std :: string signal;//倒计时结束发出信号，为空则不发出信号
        int content;//信号内容
    public:
        Timer(float duration, uint64_t receiver, const std :: string &signal, int content = 0, const std :: vector<std :: string> &tag = {});
        virtual ~Timer();
        void reset();//重置计时
        bool isActive() const;//倒计时是否结束
        virtual void update(const float &deltaTime);//更新函数
    };
    ```

- **Transparency：改变对象透明度**

    ```cpp
    class Transparency : public Entity {
    private:
        uint64_t receiver;//信号接收者
        std :: string signal;//透明度改变结束发出信号
        float current, target;//当前透明度，目标透明度
        float duration, delay, velocity;//改变时长，延时，透明度减少速度
    public:
        Transparency(uint64_t receiver, const std :: string &signal, float start, float end, float duration, float delay = 0.f, const std :: vector<std :: string> &tag = {});
        virtual ~Transparency();
        bool isActive() const;//是否完成
        virtual void update(const float &deltaTime);//更新函数
    };
    ```

#### 三. 特性与增加内容

- 大逃杀模式，地图会不断缩小。
- 更加智能的 NPC。
- 每击杀一名敌人增加 8 把飞刀。
- 音效支持。
- 小地图支持。