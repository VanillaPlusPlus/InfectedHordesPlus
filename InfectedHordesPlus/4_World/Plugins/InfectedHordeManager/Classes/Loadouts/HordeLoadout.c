class HordeLoadout
{
	private string m_Name;
	private HordeCategory m_Category;
	private ref array<string> m_Gear;
	private ref array<string> m_Loot;

   void HordeLoadout(HordeCategory category, string name, array<string> gear, array<string> loot)
   {
		m_Name = name;
		m_Category = category;
		m_Gear = gear;
		m_Loot = loot;
   }
	
	string GetName()
	{
		return m_Name;
	}
	
	HordeCategory GetCategory()
	{
		return m_Category;
	}
	
	void GetGear(out array<string> gear)
	{
		gear = m_Gear;
	}
	
	void GetLoot(out array<string> loot)
	{
		loot = m_Loot;
	}
}