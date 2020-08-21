class InfectedHorde
{
    private vector m_Position;
	private bool m_CanDelete;
	private bool m_DeleteOnlyAlive;
	private ref array<ref EntityAI> m_Infected;

   void InfectedHorde(vector pos, bool canDelete, bool deleteAlive)
   {
		m_Position = pos;
		m_Infected = new array<ref EntityAI>;
		m_CanDelete = canDelete;
		m_DeleteOnlyAlive = deleteAlive;
   }
	
	void ~InfectedHorde()
	{		
		if(m_CanDelete)
		{
			foreach(EntityAI infected : m_Infected)
			{
				if(m_DeleteOnlyAlive)
				{
					if(infected.IsAlive())
					{
						GetGame().ObjectDelete(infected);	
					}
					
					if(!infected.IsAlive())
					{
						continue;
					}
				}
				
				if(!m_DeleteOnlyAlive)
				{
					GetGame().ObjectDelete(infected);
				}				
			}
		}
		
		delete m_Infected;
	}
	
	bool CanRelease()
	{
		foreach(EntityAI entity : m_Infected)
		{
			if(entity.IsAlive())
			{
				return false;
			}
		}
		
		return true;
	}
	
	void AddInfected(EntityAI infected)
	{
		m_Infected.Insert(infected);
	}
		
	vector GetPosition()
	{
		return m_Position;
	}
}