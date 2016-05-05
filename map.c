#include "detector.h"

/*
	return PCN that free in pool type
*/
int find_free(struct pool_info *pool,int type)
{
	int i;
	if(type==POOL_SCM)
	{
		for(i=0;i<pool->chunk_scm;i++)
		{
			if(pool->revTab[i].lcn==-1)
			{
				return i;
			}
		}
		return -1;
	}
	else if(type==POOL_SSD)
	{
		for(i=pool->chunk_scm;i<(pool->chunk_scm+pool->chunk_ssd);i++)
		{
			if(pool->revTab[i].lcn==-1)
			{
				return i;
			}
		}
		return -1;
	}
	else
	{
		for(i=pool->chunk_scm+pool->chunk_ssd;i<pool->chunk_sum;i++)
		{
			if(pool->revTab[i].lcn==-1)
			{
				return i;
			}			
		}
		return -1;
	}
}//end

void update_map(struct pool_info *pool,int i)
{
	int free_chk;
	if(pool->chunk[i].location_next==POOL_SCM)
	{
		if(pool->chunk[i].location==POOL_SCM)
		{
			pool->migrate_scm_scm++;
		}
		else if(pool->chunk[i].location==POOL_SSD)
		{
			free_chk=find_free(pool,POOL_SSD)
			if(free_chk!=-1)
			{
				pool->migrate_scm_ssd++;
				pool->revTab[pool->mapTab[i].pcn].lcn=-1;	//free the old space

				pool->mapTab[i].pcn=free_chk;
				pool->revTab[free_chk].lcn=i;
			}//else give up migration
		}
		else
		{
			free_chk=find_free(pool,POOL_HDD)
			if(free_chk!=-1)
			{
				pool->migrate_ssd_hdd++;
				pool->revTab[pool->mapTab[i].pcn].lcn=-1;
				
				pool->mapTab[i].pcn=free_chk;
				pool->revTab[free_chk].lcn=i;
			}
		}
	}//if
	else if(pool->chunk[i].location_next==POOL_SSD)
	{
	
	}
	else //if(pool->chunk[i].location_next==POOL_HDD)
	{
	
	}

}
