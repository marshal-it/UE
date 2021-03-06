MLoader("MyLua.Libs.Core.GlobalNS");
MLoader("MyLua.Libs.Core.StaticClass");
MLoader("MyLua.Libs.Tools.UtilEngineWrap");

local M = GlobalNS.StaticClass();
local this = M;
M.clsName = "UtilMsg";
GlobalNS[M.clsName] = M;

function M.init()

end

function M.sendMsg(id, msg, bnet)
    if(bnet == nil or bnet == true) then
        -- 从网络发送
		Ctx.mNetMgr:sendCmd(id, msg, bnet);
    else
        -- 直接放在本地数据缓存
    end
end

function M.sendMsgRpc(id, rpc, msg, bnet)
    if(bnet == nil or bnet == true) then
        -- 从网络发送
		Ctx.mNetMgr:sendCmdRpc(id, rpc, msg, bnet);
    else
        -- 直接放在本地数据缓存
    end
end

M.init();   -- 初始化

return M;