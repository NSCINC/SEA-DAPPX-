-- InvestmentContract
InvestmentContract = {}
InvestmentContract.__index = InvestmentContract

-- Cria um novo contrato de investimento
function InvestmentContract.new(owner)
    local self = setmetatable({}, InvestmentContract)
    self.owner = owner
    self.plans = {}
    return self
end

-- Adiciona um novo plano de investimento
function InvestmentContract:add_plan(plan_name, initial_investment)
    self.plans[plan_name] = initial_investment
    print("Plano de investimento adicionado:", plan_name, "com investimento inicial de:", initial_investment)
end

-- Investimento em um plano existente
function InvestmentContract:invest(plan_name, amount, investor_address)
    if self.plans[plan_name] then
        print("Investimento de:", amount, "no plano:", plan_name, "por:", investor_address)
    else
        print("Plano não encontrado:", plan_name)
    end
end

-- Inicialização do contrato
contract = InvestmentContract.new("owner_address")

-- Processamento de entradas do programa via linha de comando
local command = arg[1]
if command == "add_plan" then
    contract:add_plan(arg[2], tonumber(arg[3]))
elseif command == "invest" then
    contract:invest(arg[2], tonumber(arg[3]), arg[4])
end
