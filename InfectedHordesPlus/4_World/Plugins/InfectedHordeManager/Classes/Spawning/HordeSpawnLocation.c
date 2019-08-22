class HordeSpawnLocation
{
   private string m_Name;
	private HordeCategory m_Category;
   private int m_SpawnOffset;
	private vector m_Position;

	[NonSerialized()]
	private bool m_IsAlive;

   void HordeSpawnLocation(HordeCategory category, string name, vector pos, int spawnOffset = 50)
   {
      m_Name = name;
		m_Category = category;
      m_Position = pos;
		m_SpawnOffset = spawnOffset;
		m_IsAlive = false;
   }

   string GetName()
   {
      return m_Name;
   }
	
	vector GetOffsetVector(inout vector spawn)
	{
      spawn[0] = spawn[0] + Math.RandomIntInclusive(-m_SpawnOffset, m_SpawnOffset);
      spawn[2] = spawn[2] + Math.RandomIntInclusive(-m_SpawnOffset, m_SpawnOffset);
			
		return spawn;
	}
	
	HordeCategory GetCategory()
	{
		return m_Category;
	}

   vector GetPosition()
   {
      return m_Position;
   }
	
	bool IsAlive()
	{
		return m_IsAlive;
	}
	
	void SetAlive()
	{
		m_IsAlive = !m_IsAlive;
	}
}