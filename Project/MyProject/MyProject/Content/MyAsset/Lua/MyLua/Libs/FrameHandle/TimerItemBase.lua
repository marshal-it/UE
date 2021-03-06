MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.DelayHandle.IDelayHandleItem");

--[[
    @brief 定时器，这个是不断增长的
]]

local M = GlobalNS.Class(GlobalNS.IDelayHandleItem);
M.clsName = "TimerItemBase";
GlobalNS[M.clsName] = M;

function M:ctor()
    self.mInternal = 1;            -- 定时器间隔
    self.mTotalTime = 1;           -- 总共定时器时间
    self.mCurRunTime = 0;          -- 当前定时器运行的时间
    self.mCurCallTime = 0;         -- 当前定时器已经调用的时间
    self.mIsInfineLoop = false;     -- 是否是无限循环
    self.mIntervalLeftTime = 0;    -- 定时器调用间隔剩余时间
    self.mTimerDispatch = GlobalNS.new(GlobalNS.TimerFunctionObject);         -- 定时器分发
    self.mIsDisposed = false;        -- 是否已经被释放
    self.mIsContinuous = false;     -- 是否是连续的定时器
end

function M:setFuncObject(pThis, func, eventId)
    self.mTimerDispatch:setPThisAndHandle(pThis, func, eventId);
end

function M:setTotalTime(value)
    self.mTotalTime = value;
end

function M:getRunTime()
    return self.mCurRunTime;
end

function M:getCallTime()
    return self.mCurCallTime;
end

function M:getLeftRunTime()
    return self.mTotalTime - self.mCurRunTime;
end

function M:getLeftCallTime()
    return self.mTotalTime - self.mCurCallTime;
end

-- 在调用回调函数之前处理
function M:onPreCallBack()
    
end

function M:OnTimer(delta)
    if self.mIsDisposed then
        return;
    end

    self.mCurRunTime = self.mCurRunTime + delta;
    if(self.mCurRunTime > self.mTotalTime) then
        self.mCurRunTime = self.mTotalTime;
    end
    self.mIntervalLeftTime = self.mIntervalLeftTime + delta;

    if self.mIsInfineLoop then
        self:checkAndDispatch();
    else
        if self.mCurRunTime >= self.mTotalTime then
            self:disposeAndDispatch();
        else
            self:checkAndDispatch();
        end
    end
end

function M:disposeAndDispatch()
    if(self.mIsContinuous) then
        self:continueDisposeAndDispatch();
    else
        self:discontinueDisposeAndDispatch();
    end
end

function M:continueDisposeAndDispatch()
    self.mIsDisposed = true;
    
    while (self.mIntervalLeftTime >= self.mInternal and self.mCurCallTime < self.mTotalTime) do
        self.mCurCallTime = self.mCurCallTime + self.mInternal;
        self.mIntervalLeftTime = self.mIntervalLeftTime - self.mInternal;
        self:onPreCallBack();

        if (self.mTimerDispatch:isValid()) then
            self.mTimerDispatch:call(self);
        end
    end
end

function M:discontinueDisposeAndDispatch()
    self.mIsDisposed = true;
    self.mCurCallTime = self.mTotalTime;
    self:onPreCallBack();
    
    if (self.mTimerDispatch:isValid()) then
        self.mTimerDispatch:call(self);
    end
end

function M:checkAndDispatch()
    if(self.mIsContinuous) then
        self:continueCheckAndDispatch();
    else
        self:discontinueCheckAndDispatch();
    end
end

-- 连续的定时器
function M:continueCheckAndDispatch()
    while (self.mIntervalLeftTime >= self.mInternal) do
        self.mCurCallTime = self.mCurCallTime + self.mInternal;
        self.mIntervalLeftTime = self.mIntervalLeftTime - self.mInternal;
        self:onPreCallBack();

        if (self.mTimerDispatch:isValid()) then
            self.mTimerDispatch:call(self);
        end
    end
end

-- 不连续的定时器
function M:discontinueCheckAndDispatch()
    if (self.mIntervalLeftTime >= self.mInternal) then
        self.mCurCallTime = self.mCurCallTime + ((math.floor(self.mIntervalLeftTime / self.mInternal)) * self.mInternal);
        self.mIntervalLeftTime = self.mIntervalLeftTime % self.mInternal;   -- 只保留余数
        self:onPreCallBack();

        if (self.mTimerDispatch:isValid()) then
            self.mTimerDispatch:call(self);
        end
    end
end

function M:reset()
    self.mCurRunTime = 0;
    self.mCurCallTime = 0;
    self.mIntervalLeftTime = 0;
    self.mIsDisposed = false;
end

function M:setClientDispose()
    
end

function M:getClientDispose()
    return false;
end

function M:start(priority)
    Ctx.mTimerMgr:addTimer(self);
end

function M:stop()
    Ctx.mTimerMgr:removeObject(self);
end

return M;