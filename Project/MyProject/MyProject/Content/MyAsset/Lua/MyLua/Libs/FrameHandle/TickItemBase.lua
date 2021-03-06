MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.Class");
MLoader("MyLua.Libs.FrameHandle.ITickedObject");

local M = GlobalNS.Class(GlobalNS.ITickedObject);
M.clsName = "TickItemBase";
GlobalNS[M.clsName] = M;

function M:ctor()
	
end

function M:onTick(delta, tickMode)
	
end

function M:setClientDispose(isDispose)

end

function M:isClientDispose()
	return false;
end

function M:addSelfTick(priority)
	-- Test 延迟添加
	-- Ctx.mTickMgr:incDepth();
    Ctx.mTickMgr:addTick(self, priority);
	-- Ctx.mTickMgr:decDepth();
end

function M:removeSelfTick()
    Ctx.mTickMgr:removeTick(self);
end

return M;