package samples.hadoop.hdg.ch2;

import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class MaxTemperature {
	
	static class MaxTemperatureMapper extends Mapper<LongWritable, Text, Text, IntWritable> {
		
		private static final int MISSING = 9999;
		
		protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
			
			String line = value.toString();
			String year = line.substring(15,19);
			int airTemp;
			if(line.charAt(87) == '+'){
				airTemp = Integer.parseInt(line.substring(88,92));
			}
			else{
				airTemp = Integer.parseInt(line.substring(87, 92));
			}
			
			String quality = line.substring(92, 93);
			if( airTemp != MISSING && quality.matches("[01459]") ){
				context.write(new Text(year), new IntWritable(airTemp));
			}
		};
	}
	
	static class MaxTemperatureReducer extends Reducer<Text, IntWritable, Text, IntWritable> {
		protected void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException ,InterruptedException {
			int maxValue = Integer.MIN_VALUE;
			for( IntWritable value: values) {
				maxValue = Math.max(maxValue, value.get());
			}
			context.write(key, new IntWritable(maxValue));
		};
	}
	
	public static void main(String[] args) throws Exception {
		if( args.length != 2 ){
			System.err.println("Usage: MaxTemperature <input path> <output path>");
			System.exit(-1);
		}
		
		Job job = new Job();
		job.setJarByClass(MaxTemperature.class);
		
		FileInputFormat.addInputPath(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		
		job.setMapperClass(MaxTemperatureMapper.class);
		job.setReducerClass(MaxTemperatureReducer.class);
		
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);
		
		System.exit(job.waitForCompletion(true) ? 0 : 1);
		
	}
	

}
