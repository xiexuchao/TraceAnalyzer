#include "pool.h"

int warmup(struct pool_info *pool)
{
	//for ascii trace
	double time;
	unsigned int dev;
	long long lba;
	unsigned int size;
	unsigned int type;

	unsigned int index=0;
	long long lba_max=0,lba_min=0x7fffffffffffffff;
	unsigned int chk_id;
	
	while(fgets(pool->buffer,SIZE_BUFFER,pool->file_trace))
	{
		sscanf(pool->buffer,"%lf %d %lld %d %d",&time,&dev,&lba,&size,&type);
		index++;
		if(index%1000000==0)
		{
			printf("scanning(%s)%d\n",pool->filename_trace,index);
		}
		if(index==1)
		{
			pool->time_start=(long long)(time*1000);	//ms-->us
		}
		pool->time_end=(long long)(time*1000);

		if(lba<lba_min)
		{
			lba_min=lba;
		}
		if(lba>lba_max)
		{
			lba_max=lba;
		}

		chk_id=(int)(lba/(pool->size_chk*2048));
		if(pool->record_all[chk_id].accessed==0)
		{
			pool->chunk_all++;
			pool->record_all[chk_id].accessed=1;
		}
	}
	pool->chunk_min=(int)(lba_min/(pool->size_chk*1024*2));
	pool->chunk_max=(int)(lba_max/(pool->size_chk*1024*2));
	printf("------------------------Chunks: min=%d, max=%d, total=%d, exactly=%d------------------------\n",
		pool->chunk_min,pool->chunk_max,pool->chunk_max-pool->chunk_min+1,pool->chunk_all);

	//reopen trace file
	fclose(pool->file_trace);
	pool->file_trace=fopen(pool->filename_trace,"r");

	return pool->chunk_max-pool->chunk_min+1;
}