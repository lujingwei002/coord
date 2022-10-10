
class TestAction : public testing::Test {
public:
    static void SetUpTestCase() {
    }
    static void TearDownTestCase() {
    }

    void SetUp() {
    }

    void TearDown() {
    } 
public:
};

TEST_F(TestAction, Basic) {
    auto anim = coorda->Action->Begin();
    anim->Run(
        anim->Sequence(
            anim->Sequence(
                anim->Call([this](coord::action::Action* action) {
                    action->Next();
                }),
                nullptr
            ),
            anim->Wait(100),
            anim->Parallel(
                anim->Wait(200),
                anim->Call([this](coord::action::Action* action) {
                    action->Next();
                }),
                anim->Call([this](coord::action::Action* action) {
                    action->Next();
                }),
                nullptr
            ),
            anim->Call([this](coord::action::Action* action) {
                action->Next();
            }),
            anim->Call([this](coord::action::Action* action) {
                action->Next();
                coorda->Destory(0);
            }),
            nullptr
        )
    );
    //coorda->loopTest();
}

