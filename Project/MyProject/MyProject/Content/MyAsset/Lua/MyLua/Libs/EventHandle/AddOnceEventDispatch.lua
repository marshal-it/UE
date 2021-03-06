MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.EventHandle.EventDispatch");

--[[
    @brief 事件回调函数只能添加一次
]]

local M = GlobalNS.Class(GlobalNS.EventDispatch);
M.clsName = "AddOnceEventDispatch";
GlobalNS[M.clsName] = M;

function M:ctor(eventId_)
    
end

function M:addEventHandle(pThis, handle, eventId)
    -- 这个判断说明相同的函数只能加一次，但是如果不同资源使用相同的回调函数就会有问题，但是这个判断可以保证只添加一次函数，值得，因此不同资源需要不同回调函数
    if (not self:isExistEventHandle(pThis, handle, eventId)) then
        M.super.addEventHandle(self, pThis, handle, eventId);
    end
end

return M;