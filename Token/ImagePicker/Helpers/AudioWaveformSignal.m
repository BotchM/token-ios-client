#import "AudioWaveformSignal.h"

//#import "opus.h"
//#import "opusfile.h"

#import "AudioWaveform.h"

#import "SharedMediaUtils.h"
#import "PSKeyValueEncoder.h"
#import "PSKeyValueDecoder.h"

@implementation AudioWaveformSignal

+ (AudioWaveform *)waveformForPath:(NSString *)path {
//    if (![[NSFileManager defaultManager] fileExistsAtPath:path]) {
//        return nil;
//    }
//    
//    int openError = OPUS_OK;
//    OggOpusFile *opusFile = op_open_file([path UTF8String], &openError);
//    if (opusFile == NULL || openError != OPUS_OK)
//    {
//        TGLog(@"[waveformForPath op_open_file failed: %d]", openError);
//        return nil;
//    } else {
//        //_isSeekable = op_seekable(_opusFile);
//        int64_t totalSamples = op_pcm_total(opusFile, -1);
//        int32_t resultSamples = 100;
//        int32_t sampleRate = (int32_t)(MAX(1, totalSamples / resultSamples));
//        
//        NSMutableData *samplesData = [[NSMutableData alloc] initWithLength:100 * 2];
//        uint16_t *samples = samplesData.mutableBytes;
//        
//        int bufferSize = 1024 * 128;
//        int16_t *sampleBuffer = malloc(bufferSize);
//        uint64_t sampleIndex = 0;
//        uint16_t peakSample = 0;
//        
//        int index = 0;
//        
//        while (true) {
//            int readSamples = op_read(opusFile, sampleBuffer, bufferSize / 2, NULL);
//            for (int i = 0; i < readSamples; i++) {
//                uint16_t sample = (uint16_t)ABS(sampleBuffer[i]);
//                if (sample > peakSample) {
//                    peakSample = sample;
//                }
//                if (sampleIndex++ % sampleRate == 0) {
//                    if (index < resultSamples) {
//                        samples[index++] = peakSample;
//                    }
//                    peakSample = 0;
//                }
//            }
//            if (readSamples == 0) {
//                break;
//            }
//        }
//        
//        int64_t sumSamples = 0;
//        for (int i = 0; i < resultSamples; i++) {
//            sumSamples += samples[i];
//        }
//        uint16_t peak = (uint16_t)(sumSamples * 1.8f / resultSamples);
//        if (peak < 2500) {
//            peak = 2500;
//        }
//        
//        for (int i = 0; i < resultSamples; i++) {
//            uint16_t sample = (uint16_t)((int64_t)samples[i]);
//            if (sample > peak) {
//                samples[i] = peak;
//            }
//        }
//        
//        free(sampleBuffer);
//        op_free(opusFile);
//        
//        AudioWaveform *waveform = [[AudioWaveform alloc] initWithSamples:samplesData peak:peak];
//        
//        NSData *bitstream = [waveform bitstream];
//        waveform = [[AudioWaveform alloc] initWithBitstream:bitstream bitsPerSample:5];
//        
//        return waveform;
//    }
    return nil;
}

+ (SSignal *)audioWaveformForFileAtPath:(NSString *)path duration:(NSTimeInterval)__unused duration {
    return [[SSignal alloc] initWithGenerator:^id<SDisposable>(SSubscriber *subscriber) {
        NSData *key = [[[NSString alloc] initWithFormat:@"AudioWaveform-%@", path] dataUsingEncoding:NSUTF8StringEncoding];
        [[SharedMediaUtils sharedMediaTemporaryPersistentCache] getValueForKey:key completion:^(NSData *data) {
            if (data != nil) {
                PSKeyValueDecoder *decoder = [[PSKeyValueDecoder alloc] initWithData:data];
                AudioWaveform *waveform = [[AudioWaveform alloc] initWithKeyValueCoder:decoder];
                [subscriber putNext:waveform];
                [subscriber putCompletion];
            } else {
                [[SQueue concurrentDefaultQueue] dispatch:^{
                    AudioWaveform *waveform = [self waveformForPath:path];
                    if (waveform == nil) {
                        [subscriber putError:nil];
                    } else {
                        PSKeyValueEncoder *encoder = [[PSKeyValueEncoder alloc] init];
                        [waveform encodeWithKeyValueCoder:encoder];
                        [[SharedMediaUtils sharedMediaTemporaryPersistentCache] setValue:[encoder data] forKey:key];
                        
                        [subscriber putNext:waveform];
                        [subscriber putCompletion];
                    }
                }];
            }
        }];
        return nil;
    }];
}

@end
